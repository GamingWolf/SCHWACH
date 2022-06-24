#ifndef MENU_H
#define MENU_H

#include <Arduino.h>
#include <vector>
#include "MenuItem.h"

class Menu
{
public:
    Menu();

    void generateMenu();
    void getActiveMenuItem();
    void printMenu();
    void printMenuItem(int id);

protected:
    std::vector<MenuItem *> menuItems;
};

#endif