#include "input.h"

Terminal terminal;
Keyboard keyboard;

Input::Input()
{
}

void Input::init()
{
    terminal.init();

    // White == Data == PIN 32
    // Green == Clock == PIN 33
    // Red == 5V
    // Yellow == GND
    keyboard.init();
}

void Input::setMenu(Menu *newMenu)
{
    terminal.setMenu(newMenu);
    keyboard.setMenu(newMenu);
}

void Input::setDevice(Device *newDevice)
{
    terminal.setDevice(newDevice);
    keyboard.setDevice(newDevice);
}

void Input::read()
{
    terminal.read();
    keyboard.read();
}