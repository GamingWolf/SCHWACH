#include <Arduino.h>
#include <ArduinoJson.h>
#include <vector>

#include "mqttClientWrapper.h"

#define MQTT_MAX_PACKET_SIZE 4096

WiFiClient wifiClient;
PubSubClient client(wifiClient);

StaticJsonDocument<4096> jsonDoc;

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

    client.setBufferSize(MQTT_MAX_PACKET_SIZE);
}

String MQTTClientWrapper::getMessage()
{
    return lastMessage;
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
            LogUtils::xprintf("Connected");
            // Once connected, publish an announcement...
            client.publish(publishChannel, "testing...");
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(client.state());
            LogUtils::xprintf(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}

void MQTTClientWrapper::callback(char *topic, byte *payload, unsigned int length)
{

    // as byte and char have the same length, we can just
    // lie to the compiler and use char
    payload[length] = '\0';
    String s = String((char *)payload);

    DeserializationError error = deserializeJson(jsonDoc, s);
    if (error)
    {
        LogUtils::xprintf("deserializeJson() failed");
        LogUtils::xprintf(error.c_str());
        return;
    }

    String topicStr = String(topic);
    if (topicStr.startsWith("manifest/") && !topicStr.equals("manifest/broadcast"))
    {
        // remove the first 8 characters from the string
        // This leaves just the name of the device
        topicStr.remove(0, 9);

        // check all devices and exit if it exists arleady
        for (int i = 0; i < devices->size(); i++)
        {
            if (topicStr.equals(devices->at(i).getName()))
            {
                return;
            }
        }

        std::vector<DeviceOption> deviceOptions;
        for (size_t i = 0; i < jsonDoc.size(); i++)
        {

            String name = jsonDoc[i]["name"].as<String>();
            String topicName = jsonDoc[i]["topicName"].as<String>();
            String description = jsonDoc[i]["description"].as<String>();
            String type = jsonDoc[i]["type"].as<String>();

            auto jsonOptions = jsonDoc[i]["options"];
            std::vector<DeviceOptionChoice> options;
            for (int i = 0; i < jsonOptions.size(); i++)
            {
                String newOptionName = jsonOptions[i]["choiceName"].as<String>();
                String newOptionValue = jsonOptions[i]["choiceValue"].as<String>();
                auto newChoice = DeviceOptionChoice(newOptionName, newOptionValue);
                options.push_back(newChoice);
            }

            if (jsonOptions.size() == 0)
            {
                auto newChoice = DeviceOptionChoice("Listen", "");
                options.push_back(newChoice);
            }

            DeviceOption option = DeviceOption(name, topicName, description, type, options);
            deviceOptions.push_back(option);
        }
        Device device = Device(topicStr, deviceOptions);
        LogUtils::xprintf("New device found: %s", device.getName().c_str());
        devices->push_back(device);
    }
    else
    {
        // LogUtils::xprintf("-------new message from broker-----");
        // Serial.print("channel:");
        // LogUtils::xprintf(topic);
        // Serial.print("data:");
        // Serial.write(payload, length);
        // LogUtils::xprintf(" ");
        lastMessage = jsonDoc["data"].as<String>();
        // LogUtils::xprintf("%s", lastMessage);
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

void MQTTClientWrapper::unsubscribe(char *channel)
{
    if (!client.connected())
    {
        reconnect();
    }
    client.unsubscribe(channel);
    lastMessage = "";
}

void MQTTClientWrapper::loop()
{
    if (client.connected())
    {
        client.loop();
    }
    else
    {
        reconnect();
    }
}