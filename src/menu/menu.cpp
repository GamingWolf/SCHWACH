#include "menu.h"

Menu::Menu(int intId, String strName, String strDescription)
{
    id = intId;
    name = strName;
    description = strDescription;
}

void Menu::init(LcdDisplay **newDisplay)
{
    lcdDisplay = *newDisplay;
}

Menu Menu::getMenu()
{
    return *this;
}

int Menu::getSelectedIndex()
{
    return selectedIndex;
}

int Menu::getId()
{
    return id;
}

String Menu::getName()
{
    return name;
}

String Menu::getDescription()
{
    return description;
}

void Menu::generateMenu()
{
    subMenus.push_back(new Menu(0, "Devices", "List of Devices"));
    subMenus.push_back(new Menu(1, "Settings"));
    subMenus.push_back(new Menu(2, "About"));
    subMenus.push_back(new Menu(3, "Console"));
}

void Menu::increaseSelectedIndex()
{
    if (selectedIndex < subMenus.size() - 1)
    {
        selectedIndex++;
    }
}

void Menu::decreaseSelectedIndex()
{
    if (selectedIndex > 0)
    {
        selectedIndex--;
    }
}

void Menu::printMenu()
{
    Serial.println("Printing menu");
    String firstMenuLine, secondMenuLine = "";
    for (int i = 0; i < subMenus.size(); i++)
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
            secondMenuLine += subMenus[i]->getDescription();
        }
        else
        {
            firstMenuLine += "";
        }

        firstMenuLine += subMenus[i]->getName();
        firstMenuLine += " ";
    }

    lcdDisplay->setFirstLine(firstMenuLine);
    lcdDisplay->setSecondLine(secondMenuLine);
}

void Menu::printDescription()
{
    lcdDisplay->setSecondLine(subMenus[selectedIndex]->getDescription());
}

void Menu::printName()
{
    lcdDisplay->setFirstLine(subMenus[selectedIndex]->getName());
}