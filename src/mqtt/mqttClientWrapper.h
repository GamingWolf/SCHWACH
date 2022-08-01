#ifndef MQTT_CLIENT_WRAPPER_H
#define MQTT_CLIENT_WRAPPER_H

#include <WiFi.h>
#include <WiFiSTA.h>
#include <PubSubClient.h>

#include "../menu/device.h"

class MQTTClientWrapper
{
public:
    MQTTClientWrapper();

    void init(std::vector<Device> *newDevices);
    void reconnect();
    void publishSerialData(char *channel, char *serialData);
    void loop();
    void subscribe(char *channel);
    std::vector<Device> &getDevices();
    void callback(char *topic, byte *payload, unsigned int length);

protected:
    char *mqttServer = (char *)"mqtt.castrumnubis.com";
    int mqttPort = 1883;
    char *publishChannel = (char *)"SCHWACH/log";
    std::vector<Device> *devices;
};

#endif