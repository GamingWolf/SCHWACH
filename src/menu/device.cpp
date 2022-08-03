#include "device.h"
#include "../utils/logUtils.h"

Device::Device(String name, std::vector<DeviceOption> options)
{
    deviceName = name;
    deviceOptions = options;
}

String Device::getName()
{
    return deviceName;
}

std::vector<DeviceOption> Device::getOptions()
{
    return deviceOptions;
}

void Device::showOptions()
{
    LogUtils::xprintf("Device Name:");
    LogUtils::xprintf(deviceName.c_str());
    LogUtils::xprintf("Options:");

    for (auto option : deviceOptions)
    {
        LogUtils::xprintf("Option Name: %s", option.getName().c_str());
        LogUtils::xprintf("Option Type: %s", option.getType().c_str());
        LogUtils::xprintf("Showing Options:");
        auto options = option.getOptions();
        if (options.size() > 0)
        {
            for (auto option : options)
            {
                Serial.println(option.getName());
            }
        }
        else
        {
            LogUtils::xprintf("No options");
        }
    }
}