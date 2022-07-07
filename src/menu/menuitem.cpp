#include "menuitem.h"

MenuItem::MenuItem(int id, String name, String description, bool isMenu)
{
    this->id = id;
    this->name = name;
    this->description = description;
    this->isMenu = isMenu;
}

String MenuItem::getName()
{
    return name;
}

String MenuItem::getDescription()
{
    return description;
}

bool MenuItem::IsMenu()
{
    return isMenu;
}

void MenuItem::increaseSelectedIndex()
{
    if (selectedIndex < menuItems.size() - 1)
    {
        selectedIndex++;
    }
}

void MenuItem::decreaseSelectedIndex()
{
    if (selectedIndex > 0)
    {
        selectedIndex--;
    }
}

void MenuItem::setDisplay(LcdDisplay **newDisplay)
{
    lcdDisplay = *newDisplay;
}

void MenuItem::generateMenu()
{
    //@TODO Get devices from MQTT server
    menuItems.push_back(new MenuItem(0, "HATER", "Sensor"));
    menuItems.push_back(new MenuItem(1, "Lamp", "A lamp!"));
    menuItems.push_back(new MenuItem(2, "Door"));
}

void MenuItem::printMenu()
{
    Serial.println("Printing sub menu");
    String firstMenuLine, secondMenuLine = "";
    for (int i = 0; i < menuItems.size(); i++)
    {
        if (firstMenuLine.length() >= 16 && i <= selectedIndex)
        {
            firstMenuLine = "";
        }
        else if (firstMenuLine.length() >= 16)
        {
            break;
        }

        if (i == selectedIndex)
        {
            firstMenuLine += ">";
            secondMenuLine += menuItems[i]->getDescription();
        }
        else
        {
            firstMenuLine += "";
        }

        firstMenuLine += menuItems[i]->getName();
        firstMenuLine += " ";
    }

    lcdDisplay->setFirstLine(firstMenuLine);
    lcdDisplay->setSecondLine(secondMenuLine);
}