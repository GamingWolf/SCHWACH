#ifndef DEVICE_OPTION_CHOICE_H
#define DEVICE_OPTION_CHOICE_H

#include <Arduino.h>

class DeviceOptionChoice
{
public:
    DeviceOptionChoice(String name, String value);
    String getName();
    String getValue();

private:
    String name;
    String value;
};

#endif