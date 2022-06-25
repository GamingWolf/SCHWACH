#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "menu/menu.h"
#include "display/lcdDisplay.h"

LcdDisplay *lcdDisplay;

void setup()
{
  Menu mainMenu = Menu();
  mainMenu.generateMenu();

  lcdDisplay = new LcdDisplay();

  lcdDisplay->boot();
}

void loop()
{
  lcdDisplay->clear();
  lcdDisplay->setFirstLine("    SCHWACH!");
  lcdDisplay->setSecondLine(millis() / 1000);
  delay(500);
}