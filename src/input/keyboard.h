#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <fabgl.h>

#include "../menu/menu.h"

class Keyboard
{
public:
    Keyboard();

    void printInfo();
    void init();
    void setMenu(Menu *newMenu);
    void read();

private:
    void identify();

    fabgl::PS2Controller PS2Controller;
    fabgl::Keyboard keyboard;
    Menu *menu;
};

#endif