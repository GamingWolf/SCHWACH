#include "terminal.h"
#include "../utils/logUtils.h"

Terminal::Terminal()
{
}

void Terminal::init(Menu newMenu)
{
    menu = newMenu;

    LogUtils::xprintf("\r\nInitialised\r\n");
}

void Terminal::read()
{
    if (Serial.available() > 0)
    {
        char c = Serial.read();
        switch (c)
        {
        case 'w':
            LogUtils::xprintf("Up");
            break;
        case 'd':
            LogUtils::xprintf("Right");
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
            LogUtils::xprintf("Down");
            break;
        case 'a':
            LogUtils::xprintf("Left");
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
            LogUtils::xprintf("Home");
            menu.printMenu();
            break;
        case ' ':
            LogUtils::xprintf("Select");
            menu.printMenuItem(menu.getSelectedIndex());
            break;
        default:
            LogUtils::xprintf(&c);
            break;
        }
    }
}