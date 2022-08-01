#include "terminal.h"
#include "../utils/logUtils.h"
#include "../menu/menu.h"

Terminal::Terminal()
{
}

void Terminal::init(std::vector<Device> *newDevices, MQTTClientWrapper *newMqttClientWrapper)
{
    LogUtils::xprintf("\r\nInitialised\r\n");
    devices = newDevices;
    mqttClientWrapper = newMqttClientWrapper;
}

void Terminal::setMenu(Menu *newMenu)
{
    menu = newMenu;
}

void Terminal::read()
{
    if (Serial.available() > 0)
    {
        char c = Serial.read();
        switch (c)
        {
        case 'w':
            LogUtils::xprintf("Up");
            break;
        case 'd':
            LogUtils::xprintf("Right");
            menu->increaseSelectedIndex();
            menu->printMenu();
            break;
        case 's':
            LogUtils::xprintf("Down");
            LogUtils::xprintf("%d", devices->at(0).getName());
            devices->at(0).showOptions();
            break;
        case 'a':
            LogUtils::xprintf("Left");
            menu->decreaseSelectedIndex();
            menu->printMenu();
            break;
        case 'b':
        case 'h':
            LogUtils::xprintf("Home");
            menu->printMenu();
            break;
        case ' ':
            LogUtils::xprintf("Select");
            // menu.printMenuItem(menu.getSelectedIndex());
            break;
        default:
            LogUtils::xprintf(&c);
            break;
        }
    }
}