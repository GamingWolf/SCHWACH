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

void Device::showOptions()
{
    Serial.println("-------new message from broker-----");
    Serial.print("Device Name:");
    LogUtils::xprintf(deviceName.c_str());
    Serial.print("Options:");

    for (auto option : deviceOptions)
    {
        // Serial.print("Option Name:");
        // Serial.println(option.getName());
        // Serial.print("Option Type:");
        // Serial.println(option.getType());
        for (auto option : option.getOptions())
        {
            Serial.println("Showing Options:");
            Serial.print(option);
        }
        Serial.println();
    }
}