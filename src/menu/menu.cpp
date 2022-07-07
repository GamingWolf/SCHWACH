#include "menu.h"

Menu::Menu()
{
}

void Menu::init(LcdDisplay **newDisplay)
{
    lcdDisplay = *newDisplay;
}

int Menu::getSelectedIndex()
{
    return selectedIndex;
}

bool Menu::isInSubMenu()
{
    return inSubMenu;
}

MenuItem *Menu::getActiveMenuItem()
{
    return menuItems[selectedIndex];
}

void Menu::generateMenu()
{
    menuItems.push_back(new MenuItem(0, "Devices", "List of Devices", true));
    menuItems.push_back(new MenuItem(1, "Settings"));
    menuItems.push_back(new MenuItem(2, "About"));
    menuItems.push_back(new MenuItem(3, "Console"));
}

void Menu::increaseSelectedIndex()
{
    if (selectedIndex < menuItems.size() - 1)
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

void Menu::printMenuItem(int id)
{
    Serial.println("Printing menu item");
    MenuItem *menuItem = menuItems[id];
    if (menuItem->IsMenu())
    {
        inSubMenu = true;
        menuItem->setDisplay(&lcdDisplay);
        menuItem->generateMenu();
        menuItem->printMenu();
    }
    else
    {
        lcdDisplay->setFirstLine(menuItem->getName());
        lcdDisplay->setSecondLine(menuItem->getDescription());
    }
}