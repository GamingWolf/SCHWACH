#ifndef DEVICE_OPTION_H
#define DEVICE_OPTION_H

#include <ArduinoJson.h>
#include <vector>

class DeviceOption
{
public:
    DeviceOption(const char *newName, const char *newType, std::vector<String> newOptions);
    const char *getName();
    const char *getType();
    std::vector<String> getOptions();

private:
    const char *name;
    const char *type;
    std::vector<String> options;
};
#endif