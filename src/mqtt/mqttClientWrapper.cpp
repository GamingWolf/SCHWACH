#include <Arduino.h>
#include <ArduinoJson.h>
#include <vector>

#include "mqttClientWrapper.h"

WiFiClient wifiClient;
PubSubClient client(wifiClient);

StaticJsonDocument<1024> jsonDoc;

MQTTClientWrapper::MQTTClientWrapper()
{
}

void MQTTClientWrapper::init(std::vector<Device> *newDevices)
{
    devices = newDevices;
    client.setServer(mqttServer, mqttPort);
    // client.setCallback(callback);
    client.setCallback([this](char *topic, byte *payload, unsigned int length)
                       { this->callback(topic, payload, length); });
}

void MQTTClientWrapper::reconnect()
{
    // Loop until we're reconnected
    while (!client.connected())
    {
        Serial.print("Attempting MQTT connection...");
        // Create a random client ID
        String clientId = "SCHWACH-";
        clientId += String(random(0xffff), HEX);
        // Attempt to connect
        if (client.connect(clientId.c_str()))
        {
            Serial.println("Connected");
            // Once connected, publish an announcement...
            client.publish(publishChannel, "testing...");
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}

void MQTTClientWrapper::callback(char *topic, byte *payload, unsigned int length)
{

    // Serial.println("-------new message from broker-----");
    // Serial.print("channel:");
    // Serial.println(topic);
    // Serial.print("data:");
    // Serial.write(payload, length);

    String topicStr = String(topic);
    if (topicStr.startsWith("manifest/") && !topicStr.equals("manifest/broadcast"))
    {
        // as byte and char have the same length, we can just
        // lie to the compiler and use char
        payload[length] = '\0';
        String s = String((char *)payload);

        DeserializationError error = deserializeJson(jsonDoc, s);
        if (error)
        {
            Serial.println("deserializeJson() failed");
            Serial.println(error.c_str());
            return;
        }

        // remove the first 8 characters from the string
        // This leaves just the name of the device
        topicStr.remove(0, 9);
        std::vector<DeviceOption> deviceOptions;
        for (size_t i = 0; i < jsonDoc.size(); i++)
        {

            String name = jsonDoc[i]["name"].as<String>();
            String type = jsonDoc[i]["type"].as<String>();

            auto jsonOptions = jsonDoc[i]["options"];
            std::vector<String> options;
            for (int i = 0; i < jsonOptions.size(); i++)
            {
                String newOption = jsonOptions[i].as<String>();
                options.push_back(newOption);
            }

            DeviceOption option = DeviceOption(name, type, options);
            deviceOptions.push_back(option);
        }
        Device device = Device(topicStr, deviceOptions);
        devices->push_back(device);
    }
}

void MQTTClientWrapper::publishSerialData(char *channel, char *serialData)
{
    if (!client.connected())
    {
        reconnect();
    }
    client.publish(channel, serialData);
}

void MQTTClientWrapper::subscribe(char *channel)
{
    if (!client.connected())
    {
        reconnect();
    }
    client.subscribe(channel);
}

void MQTTClientWrapper::loop()
{
    client.loop();
}