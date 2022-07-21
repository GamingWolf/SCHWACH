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

void MQTTClientWrapper::init()
{
    client.setServer(mqttServer, mqttPort);
    client.setCallback(callback);
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

    Serial.println("-------new message from broker-----");
    Serial.print("channel:");
    Serial.println(topic);
    Serial.print("data:");

    String topicStr = String(topic);

    if (topicStr.startsWith("manifest/"))
    {
        // as byte and char have the same length, we can just
        // lie to the compiler and use char
        // payload[length] = '\0';
        // String s = String((char *)payload);

        // DeserializationError error = deserializeJson(jsonDoc, s);
        // if (error)
        // {
        //     Serial.println("deserializeJson() failed");
        //     Serial.println(error.c_str());
        //     return;
        // }

        // remove the first 8 characters from the string
        // This leaves just the name of the device
        // topicStr.remove(0, 9);
        // std::vector<DeviceOption> deviceOptions;
        // for (size_t i = 0; i < jsonDoc.size(); i++)
        // {

        //     const char name = jsonDoc[i]["name"];
        //     const char type = jsonDoc[i]["type"];
        //     auto jsonOptions = jsonDoc[i]["options"].as<JsonArray>();
        //     std::vector<String> options;
        //     for (int i = 0; i < jsonOptions.size(); i++)
        //     {
        //         options.push_back(String((char *)jsonOptions[i]));
        //     }

        //     DeviceOption *option = new DeviceOption(name, type, options);
        //     deviceOptions.push_back(*option);
        // }
        // Serial.println(topicStr);
        // Device *device = new Device(topicStr, deviceOptions);
    }
}

void MQTTClientWrapper::publishSerialData(char *serialData)
{
    if (!client.connected())
    {
        reconnect();
    }
    client.publish(publishChannel, serialData);
}

void MQTTClientWrapper::subscribe(char *channel)
{
    client.subscribe(channel);
}

void MQTTClientWrapper::loop()
{
    client.loop();
}