#include "terminal.h"

Terminal::Terminal()
{
}

void Terminal::init(Menu newMenu)
{
    menu = newMenu;
    Serial.begin(115200);
    Serial.write("\r\nInitialised\r\n");
}

void Terminal::read()
{
    if (Serial.available() > 0)
    {
        char c = Serial.read();
        switch (c)
        {
        case 'w':
            Serial.println("Up");
            break;
        case 'd':
            Serial.println("Right");
            if (menu.isInSubMenu())
            {
                MenuItem *activeMenuItem = menu.getActiveMenuItem();
                activeMenuItem->increaseSelectedIndex();
                activeMenuItem->printMenu();
            }
            else
            {
                menu.increaseSelectedIndex();
                menu.printMenu();
            }
            break;
        case 's':
            Serial.println("Down");
            break;
        case 'a':
            Serial.println("Left");
            if (menu.isInSubMenu())
            {
                MenuItem *activeMenuItem = menu.getActiveMenuItem();
                activeMenuItem->decreaseSelectedIndex();
                activeMenuItem->printMenu();
            }
            else
            {
                menu.decreaseSelectedIndex();
                menu.printMenu();
            }
            break;
        case 'h':
            Serial.println("Home");
            menu.printMenu();
            break;
        case ' ':
            Serial.println("Select");
            menu.printMenuItem(menu.getSelectedIndex());
            break;
        default:
            Serial.println(c);
            break;
        }
    }
}