#ifndef TERMINAL_H
#define TERMINAL_H

#include <fabgl.h>

#include "../menu/menu.h"
#include "../menu/device.h"

class Terminal
{
public:
    Terminal();

    void init();
    void setMenu(Menu *newMenu);
    void setDevice(Device *newDevice);
    void read();

protected:
    fabgl::VGATextController displayController;
    fabgl::Terminal terminal;
    Menu *menu;
    Device *device;
};

#endif