#ifndef DEVICE_OPTION_H
#define DEVICE_OPTION_H

#include <ArduinoJson.h>
#include <vector>

class DeviceOption
{
public:
    DeviceOption(String newName, String newType, std::vector<String> newOptions);
    String getName();
    String getType();
    std::vector<String> getOptions();

private:
    String name;
    String type;
    std::vector<String> options;
};
#endif