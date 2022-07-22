#include "deviceOption.h"

DeviceOption::DeviceOption(const char *newName, const char *newType, std::vector<String> newOptions)
{
    this->name = name;
    this->type = type;
    this->options = options;
}

const char *DeviceOption::getName()
{
    return name;
}

const char *DeviceOption::getType()
{
    return type;
}

std::vector<String> DeviceOption::getOptions()
{
    return options;
}