#ifndef MENU_H
#define MENU_H

#include <Arduino.h>
#include <vector>

#include "../display/lcdDisplay.h"
#include "../mqtt/mqttClientWrapper.h"
#include "device.h"
#include "MenuItem.h"

#define MAIN_MENU -1
#define DEVICE_MENU 0
#define SETTINGS_MENU 1
#define ABOUT_MENU 2
#define CONSOLE_MENU 3
#define DEVICE_OPTION_MENU 4
#define DEVICE_OPTION_CHOICE 5

class Menu
{
public:
    Menu(int intId = 0, String strName = "", String strDescription = "");

    void init(LcdDisplay **newDisplay, std::vector<Device> *newDevices, MQTTClientWrapper *newMqttClientWrapper);

    void generateMenu();
    void printMenu();
    void printSubMenu(int index);
    void printDescription();
    void printDeviceOptions();
    void printDeviceOptionsSelection();
    void printDevices();
    void printName();
    void increaseSelectedIndex();
    void decreaseSelectedIndex();
    void executeChoice();

    // getters
    Menu getMenu();
    int getSelectedIndex();
    int getId();
    int getCurrentFlag();
    String getName();
    String getDescription();

    // deprecated
    void printMenuItem(int id);

protected:
    int id;
    bool inDeviceList = false;
    bool inDevice = false;
    bool inOptionChoice = false;
    int currentFlag = MAIN_MENU;
    String name;
    String description;
    int selectedIndex = 0;
    int selectedDevice = 0;
    int selectedDeviceOption = 0;
    int selectedDeviceOptionChoice = 0;
    std::vector<int> menuTracker;
    std::vector<Menu *> subMenus;
    std::vector<Device> *devices;
    MQTTClientWrapper *mqttClientWrapper;
    LcdDisplay *lcdDisplay;
};

#endif