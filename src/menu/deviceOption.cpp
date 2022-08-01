#include "deviceOption.h"

DeviceOption::DeviceOption(String newName, String newType, std::vector<String> newOptions)
{
    name = newName;
    type = newType;
    options = newOptions;
}

String DeviceOption::getName()
{
    return name;
}

String DeviceOption::getType()
{
    return type;
}

std::vector<String> DeviceOption::getOptions()
{
    return options;
}