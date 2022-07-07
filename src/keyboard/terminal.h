#ifndef TERMINAL_H
#define TERMINAL_H

#include <fabgl.h>

#include "../menu/menu.h"

class Terminal
{
public:
    Terminal();

    void init(Menu newMenu);
    void read();

protected:
    fabgl::VGATextController displayController;
    fabgl::Terminal terminal;
    Menu menu;
};

#endif