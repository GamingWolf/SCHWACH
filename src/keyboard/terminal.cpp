#include "terminal.h"
#include "../utils/logUtils.h"
#include "../menu/menu.h"

Terminal::Terminal()
{
}

void Terminal::init()
{
    LogUtils::xprintf("\r\nInitialised\r\n");
}

void Terminal::setMenu(Menu *newMenu)
{
    menu = newMenu;
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
            menu->increaseSelectedIndex();
            menu->printMenu();
            break;
        case 's':
            LogUtils::xprintf("Down");
            break;
        case 'a':
            LogUtils::xprintf("Left");
            menu->decreaseSelectedIndex();
            menu->printMenu();
            break;
        case 'b':
        case 'h':
            LogUtils::xprintf("Home");
            menu->printMenu();
            break;
        case ' ':
            LogUtils::xprintf("Select");
            // menu.printMenuItem(menu.getSelectedIndex());
            break;
        default:
            LogUtils::xprintf(&c);
            break;
        }
    }
}