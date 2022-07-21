#include "device.h"
#include "../utils/logUtils.h"

Device::Device(String name, std::vector<DeviceOption> options)
{
    deviceName = name;
    deviceOptions = options;
}

void Device::showOptions()
{
    Serial.println("-------new message from broker-----");
    Serial.print("channel:");
    Serial.println(deviceName.isEmpty());
    LogUtils::xprintf(deviceName.c_str());
    Serial.print("data:");

    for (size_t i = 0; i < deviceOptions.size(); i++)
    {
        Serial.print(deviceOptions.at(i).getName());
        Serial.print(" ");
        Serial.print(deviceOptions.at(i).getType());
        Serial.print(" ");
        auto deviceOptionOptions = deviceOptions.at(i).getOptions();
        for (size_t j = 0; j < deviceOptionOptions->size(); j++)
        {
            Serial.println(deviceOptionOptions[j]);
            Serial.print(" ");
        }
    }
}