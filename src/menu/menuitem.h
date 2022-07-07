#ifndef MENUITEM_H
#define MENUITEM_H

#include <Arduino.h>
#include <vector>

#include "../display/lcdDisplay.h"

class MenuItem
{
public:
    MenuItem(int id, String name, String description = "", bool isMenu = false);

    // Setters
    void setId(int id);
    void setName(String name);
    void setDescription(String description);
    void setOptions(std::vector<String> options);

    // Getters
    int getId();
    String getName();
    String getDescription();
    void getOptions();

    // Methods
    void printMenuItem();
    void printMenu();
    void generateMenu();
    bool IsMenu();
    void increaseSelectedIndex();
    void decreaseSelectedIndex();
    void setDisplay(LcdDisplay **newDisplay);

protected:
    int id;
    bool isMenu;
    String name;
    String description;
    int selectedIndex = 0;
    std::vector<String> options;
    std::vector<MenuItem *> menuItems;
    LcdDisplay *lcdDisplay;
};

#endif