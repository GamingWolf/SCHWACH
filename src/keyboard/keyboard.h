#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <fabgl.h>

class Keyboard
{
public:
    Keyboard();

    void printInfo();
    void init();
    void read();

private:
    void identify();

    fabgl::PS2Controller PS2Controller;
    fabgl::Keyboard keyboard;
};

#endif