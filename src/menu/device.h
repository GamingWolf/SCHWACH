#ifndef DEVICE_H
#define DEVICE_H

#include <Arduino.h>
#include <vector>
#include "deviceOption.h"

class Device
{
public:
    Device(String name, std::vector<DeviceOption> options);
    void showOptions();

private:
    std::vector<DeviceOption> deviceOptions;
    String deviceName;
};

#endif