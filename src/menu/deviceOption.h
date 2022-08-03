#ifndef DEVICE_OPTION_H
#define DEVICE_OPTION_H

#include <ArduinoJson.h>
#include <vector>

#include "deviceOptionChoice.h"

class DeviceOption
{
public:
    DeviceOption(String newName, String newTopicName, String newDescription, String newType, std::vector<DeviceOptionChoice> newOptions);
    String getName();
    String getTopicName();
    String getDescription();
    String getType();
    std::vector<DeviceOptionChoice> getOptions();

private:
    String name;
    String topicName;
    String description;
    String type;
    std::vector<DeviceOptionChoice> options;
};
#endif