#include <Arduino.h>
#include <SPI.h>
#include <WiFiGeneric.h>
#include <LiquidCrystal_I2C.h>
#include "menu/menu.h"
#include "display/lcdDisplay.h"
#include "keyboard/terminal.h"

LcdDisplay *lcdDisplay;
Menu mainMenu;
Terminal terminal;

void setup()
{
  lcdDisplay = new LcdDisplay();
  // lcdDisplay->boot();
  lcdDisplay->setFirstLine("    SCHWACH!");

  mainMenu.init(&lcdDisplay);
  mainMenu.generateMenu();

  terminal.init(mainMenu);

  // Black == Data == PIN 32
  //  Yellow == Clock == PIN 33
}

void loop()
{
  delay(500);

  // This can be replaced with keyboard.read() when we get it working
  terminal.read();
}