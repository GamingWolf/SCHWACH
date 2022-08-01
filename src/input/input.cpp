#include "input.h"

#include "../menu/device.h"

Terminal terminal;
Keyboard keyboard;

Input::Input()
{
}

void Input::init(std::vector<Device> *devices, MQTTClientWrapper *mqttClientWrapper)
{
    terminal.init(devices, mqttClientWrapper);

    // White == Data == PIN 32
    // Green == Clock == PIN 33
    // Red == 5V
    // Yellow == GND
    keyboard.init(devices);
}

void Input::setMenu(Menu *newMenu)
{
    terminal.setMenu(newMenu);
    keyboard.setMenu(newMenu);
}

void Input::read()
{
    terminal.read();
    keyboard.read();
}