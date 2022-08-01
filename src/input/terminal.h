#ifndef TERMINAL_H
#define TERMINAL_H

#include <fabgl.h>

#include "../menu/menu.h"
#include "../menu/device.h"
#include "../mqtt/mqttClientWrapper.h"

class Terminal
{
public:
    Terminal();

    void init(std::vector<Device> *newDevices, MQTTClientWrapper *newMqttClientWrapper);
    void setMenu(Menu *newMenu);
    void read();

protected:
    fabgl::VGATextController displayController;
    fabgl::Terminal terminal;
    MQTTClientWrapper *mqttClientWrapper;
    Menu *menu;
    std::vector<Device> *devices;
};

#endif