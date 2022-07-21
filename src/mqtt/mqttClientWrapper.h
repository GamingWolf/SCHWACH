#ifndef MQTT_CLIENT_WRAPPER_H
#define MQTT_CLIENT_WRAPPER_H

#include <WiFi.h>
#include <WiFiSTA.h>
#include <PubSubClient.h>

class MQTTClientWrapper
{
public:
    MQTTClientWrapper();

    void init();
    void reconnect();
    void publishSerialData(char *serialData);
    void loop();
    void subscribe(char *channel);
    static void callback(char *topic, byte *payload, unsigned int length);

protected:
    char *mqttServer = (char *)"mqtt.castrumnubis.com";
    int mqttPort = 1883;
    char *publishChannel = (char *)"SCHWACH/log";
};

#endif