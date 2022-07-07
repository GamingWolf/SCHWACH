#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

class LcdDisplay
{
public:
    LcdDisplay();
    LiquidCrystal_I2C getLcd();

    void setFirstLine(String text);
    void setFirstLine(unsigned long text);

    void setSecondLine(String text);
    void setSecondLine(unsigned long text);

    void clear();
    void boot();

private:
    void clearFirstLine();
    void clearSecondLine();

    LiquidCrystal_I2C lcd;
    String cleanStr = "                ";
};
#endif