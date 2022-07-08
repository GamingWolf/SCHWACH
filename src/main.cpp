#include <Arduino.h>
#include <SPI.h>
#include <WiFiGeneric.h>
#include <LiquidCrystal_I2C.h>

#include "menu/menu.h"
#include "display/lcdDisplay.h"
#include "keyboard/terminal.h"
#include "keyboard/keyboard.h"

LcdDisplay *lcdDisplay;
Menu mainMenu;
Terminal terminal;
Keyboard keyboard;

void setup()
{
  Serial.begin(115200);

  lcdDisplay = new LcdDisplay();
  // lcdDisplay->boot();
  lcdDisplay->setFirstLine("    SCHWACH!");

  mainMenu.init(&lcdDisplay);
  mainMenu.generateMenu();

  terminal.init(mainMenu);

  keyboard.init();

  // White == Data == PIN 32
  // Green == Clock == PIN 33
  // Red == 5V
  // Yellow == GND
}

void loop()
{
  // delay(500);

  // This can be replaced with keyboard.read() when we get it working
  // terminal.read();
  keyboard.read();
}