#include "menuitem.h"

MenuItem::MenuItem(int id, String name, String description, bool isMenu)
{
    this->id = id;
    this->name = name;
    this->description = description;
    this->isMenu = isMenu;
}