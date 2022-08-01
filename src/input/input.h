#ifndef INPUT_H
#define INPUT_H

#include "../menu/menu.h"
#include "../mqtt/mqttClientWrapper.h"
#include "keyboard.h"
#include "terminal.h"

class Input
{
public:
    Input();

    void init(std::vector<Device> *devices, MQTTClientWrapper *mqttClientWrapper);
    void read();
    void setMenu(Menu *newMenu);

private:
    Menu *menu;
};

#endif