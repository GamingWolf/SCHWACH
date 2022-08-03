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
        case 'd':
            LogUtils::xprintf("Right");
            menu->increaseSelectedIndex();
            break;
        case 'a':
            LogUtils::xprintf("Left");
            menu->decreaseSelectedIndex();
            break;
        case 'h':
            LogUtils::xprintf("Home");
            menu->setSelectedIndex(0);
            menu->setSelectedDevice(0);
            menu->setSelectedDeviceOption(0);
            menu->setSelectedDeviceOptionChoice(0);
            menu->printMenu();
            break;
        case 'b':
            LogUtils::xprintf("Back");
            menu->setSelectedIndex(0);
            menu->setSelectedDevice(0);
            menu->setSelectedDeviceOption(0);
            menu->setSelectedDeviceOptionChoice(0);
            switch (menu->getCurrentFlag())
            {
            case MAIN_MENU:
            case DEVICE_MENU:
            case SETTINGS_MENU:
            case ABOUT_MENU:
            case CONSOLE_MENU:
                menu->printMenu();
                break;
            case DEVICE_OPTION_MENU:
                menu->printDevices();
                break;
            case DEVICE_OPTION_CHOICE:
                menu->printDeviceOptions();
                break;
            }
            break;
        case ' ':
            LogUtils::xprintf("Select");
            menu->printSubMenu(menu->getSelectedIndex());
            break;
        default:
            LogUtils::xprintf(&c);
            break;
        }
    }
}