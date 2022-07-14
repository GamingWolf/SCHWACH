#ifndef MENU_H
#define MENU_H

#include <Arduino.h>
#include <vector>

#include "../display/lcdDisplay.h"
#include "MenuItem.h"

class Menu
{
public:
    Menu(int intId = 0, String strName = "", String strDescription = "");

    void init(LcdDisplay **newDisplay);

    void generateMenu();
    void printMenu();
    void printDescription();
    void printName();
    void increaseSelectedIndex();
    void decreaseSelectedIndex();

    // getters
    Menu getMenu();
    int getSelectedIndex();
    int getId();
    String getName();
    String getDescription();

    // deprecated
    void printMenuItem(int id);

protected:
    int id;
    String name;
    String description;
    int selectedIndex = 0;
    std::vector<int> menuTracker;
    std::vector<Menu *> subMenus;
    LcdDisplay *lcdDisplay;
};

#endif