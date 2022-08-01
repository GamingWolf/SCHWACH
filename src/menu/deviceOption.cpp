#include "deviceOption.h"

DeviceOption::DeviceOption(String newName, String newTopicName, String newDescription, String newType, std::vector<String> newOptions)
{
    name = newName;
    topicName = newTopicName;
    description = newDescription;
    type = newType;
    options = newOptions;
}

String DeviceOption::getName()
{
    return name;
}

String DeviceOption::getDescription()
{
    return description;
}

String DeviceOption::getType()
{
    return type;
}

String DeviceOption::getTopicName()
{
    return topicName;
}

std::vector<String> DeviceOption::getOptions()
{
    return options;
}