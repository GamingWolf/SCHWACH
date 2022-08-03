#include "deviceOptionChoice.h"

DeviceOptionChoice::DeviceOptionChoice(String name, String value)
{
    this->name = name;
    this->value = value;
}

String DeviceOptionChoice::getName()
{
    return name;
}

String DeviceOptionChoice::getValue()
{
    return value;
}