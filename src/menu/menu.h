#ifndef MENU_H
#define MENU_H

#include <Arduino.h>
#include <vector>

#include "../display/lcdDisplay.h"
#include "MenuItem.h"

class Menu
{
public:
    Menu();

    void init(LcdDisplay **newDisplay);

    void generateMenu();
    void printMenu();
    void printMenuItem(int id);
    bool isInSubMenu();

    void increaseSelectedIndex();
    void decreaseSelectedIndex();

    // getters
    MenuItem *getActiveMenuItem();
    int getSelectedIndex();

protected:
    int selectedIndex = 0;
    bool inSubMenu = false;
    std::vector<MenuItem *> menuItems;
    LcdDisplay *lcdDisplay;
};

#endif