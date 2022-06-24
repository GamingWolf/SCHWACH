#ifndef MENUITEM_H
#define MENUITEM_H

#include <Arduino.h>
#include <vector>

class MenuItem
{
public:
    MenuItem();

protected:
    int id;
    std::string name;
    std::string description;
    std::vector<std::string> options;
};

#endif