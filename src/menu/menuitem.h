#ifndef MENUITEM_H
#define MENUITEM_H

#include <Arduino.h>
#include <vector>

class MenuItem
{
public:
    MenuItem(int id, String name, String description, bool isMenu = false);

    // Setters
    void setId(int id);
    void setName(String name);
    void setDescription(String description);
    void setOptions(std::vector<String> options);

    // Getters
    void getId();
    void getName();
    void getDescription();
    void getOptions();
    void getIsMenu();

    // Methods
    void printMenuItem();

protected:
    int id;
    bool isMenu;
    String name;
    String description;
    std::vector<String> options;
};

#endif