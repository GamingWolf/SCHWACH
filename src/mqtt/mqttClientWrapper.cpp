#include <Arduino.h>

#include "mqttClientWrapper.h"

WiFiClient wifiClient;
PubSubClient client(wifiClient);

MQTTClientWrapper::MQTTClientWrapper()
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
    Serial.write(payload, length);
    Serial.println();
}

void MQTTClientWrapper::publishSerialData(char *serialData)
{
    if (!client.connected())
    {
        reconnect();
    }
    client.publish(publishChannel, serialData);
}

void MQTTClientWrapper::loop()
{
    client.loop();
}