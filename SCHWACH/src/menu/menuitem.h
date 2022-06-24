#ifndef MENUITEM_H
#define MENUITEM_H

#include <Arduino.h>
#include <vector>

class MenuItem
{
public:
    MenuItem();

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

    // Methods
    void printMenuItem();

protected:
    int id;
    String name;
    String description;
    std::vector<String> options;
};

#endif