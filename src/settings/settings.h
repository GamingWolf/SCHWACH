#ifndef SETTINGS_H
#define SETTINGS_H

class Settings
{
public:
    Settings();

    void init();
    void read();
    void setMenu(Menu *newMenu);
};

#endif