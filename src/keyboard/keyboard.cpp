#include "keyboard.h"
#include "../utils/logUtils.h"

Keyboard::Keyboard()
{
}

void Keyboard::init()
{
    // Enable the PS2 Controller on PIN 33 for CLK and PIN 32 for DAT
    PS2Controller.begin(GPIO_NUM_33, GPIO_NUM_32);

    // initialize keyboard on port 0 (PIN33=CLK, PIN32=DAT)
    keyboard.begin(true, true, 0);
    keyboard.setLayout(&fabgl::GermanLayout);

    identify();
}

void Keyboard::identify()
{
    if (keyboard.isKeyboardAvailable())
    {
        switch (keyboard.identify())
        {
        case PS2DeviceType::OldATKeyboard:
            LogUtils::xprintf("\"Old AT Keyboard\"");
            break;
        case PS2DeviceType::MouseStandard:
            LogUtils::xprintf("\"Standard Mouse\"");
            break;
        case PS2DeviceType::MouseWithScrollWheel:
            LogUtils::xprintf("\"Mouse with scroll wheel\"");
            break;
        case PS2DeviceType::Mouse5Buttons:
            LogUtils::xprintf("\"5 Buttons Mouse\"");
            break;
        case PS2DeviceType::MF2KeyboardWithTranslation:
            LogUtils::xprintf("\"MF2 Keyboard with translation\"");
            break;
        case PS2DeviceType::M2Keyboard:
            LogUtils::xprintf("\"MF2 keyboard\"");
            break;
        default:
            LogUtils::xprintf("\"Unknown\"");
            break;
        }
        LogUtils::xprintf("\r\n", keyboard.getLayout()->name);
        LogUtils::xprintf("Keyboard Layout: \"%s\"\r\n", keyboard.getLayout()->name);
    }
    else
        LogUtils::xprintf("Keyboard Error!\r\n");
}

void Keyboard::read()
{
    if (keyboard.virtualKeyAvailable())
    {
        // ascii mode (show ASCIIl, VirtualKeys and scancodes)
        VirtualKeyItem item;
        if (keyboard.getNextVirtualKey(&item))
        {
            LogUtils::xprintf("%s: ", keyboard.virtualKeyToString(item.vk));
            LogUtils::xprintf("\tASCII = 0x%02X\t", item.ASCII);
            if (item.ASCII >= ' ')
                LogUtils::xprintf("'%c'", item.ASCII);
            LogUtils::xprintf("\t%s", item.down ? "DN" : "UP");
            LogUtils::xprintf("\t[");
            for (int i = 0; i < 8 && item.scancode[i] != 0; ++i)
                LogUtils::xprintf("%02X ", item.scancode[i]);
            LogUtils::xprintf("]");
            LogUtils::xprintf("\r\n");
        }
    }
}