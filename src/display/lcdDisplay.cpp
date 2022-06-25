#include "lcdDisplay.h"

#include <LiquidCrystal_I2C.h>

LcdDisplay::LcdDisplay() : lcd(0x27, 16, 2)
{
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
}

LiquidCrystal_I2C LcdDisplay::getLcd()
{
    return lcd;
}

void LcdDisplay::boot()
{
    for (int i = 0; i < 3; i++)
    {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("    SCHWACH!");
        lcd.setCursor(0, 1);

        String progress = "|";
        for (int j = 0; j < 16; j++)
        {
            lcd.print(progress);
            delay(100);
            progress += "|";
        }
    }
}

void LcdDisplay::setFirstLine(String text)
{
    lcd.setCursor(0, 0);
    lcd.print(text);
}
void LcdDisplay::setFirstLine(unsigned long text)
{
    lcd.setCursor(0, 0);
    lcd.print(text);
}

void LcdDisplay::setSecondLine(String text)
{
    lcd.setCursor(0, 1);
    lcd.print(text);
}
void LcdDisplay::setSecondLine(unsigned long text)
{
    lcd.setCursor(0, 1);
    lcd.print(text);
}

void LcdDisplay::clear()
{
    lcd.clear();
}