#include <Arduino.h>
#include <SPI.h>
#include <WiFiGeneric.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <LiquidCrystal_I2C.h>

#include "menu/menu.h"
#include "display/lcdDisplay.h"
#include "input/input.h"
#include "mqtt/mqttClientWrapper.h"

LcdDisplay *lcdDisplay;
Menu mainMenu;
Input input;
MQTTClientWrapper mqttClientWrapper;
std::vector<Device> devices;

int wifiUpdateInterval = 20000;
bool disconnected = false;

char ssid[] = "masterplan";
const char *password = "J4rv1s2013W1ls0n2017";

void checkWifi()
{
  if (WiFi.status() != WL_CONNECTED && !disconnected)
  {
    disconnected = true;
    lcdDisplay->setFirstLine("WiFi failed!");
    lcdDisplay->setSecondLine("Reconnecting...");
    WiFi.reconnect();
  }

  if (WiFi.status() == WL_CONNECTED && disconnected)
  {
    lcdDisplay->setFirstLine("SCHWACH!");
    lcdDisplay->setSecondLine("WiFi Connected");
    Serial.print("Connected to: ");
    Serial.println(WiFi.SSID());
    disconnected = false;
  }
}

void setupWifi()
{
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  lcdDisplay->setFirstLine("Connecting to WiFi");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  int count = 1;
  String dots = ".";
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    if (count < 16)
    {
      dots += ".";
    }
    else
    {
      dots = ".";
      count = 1;
    }
    lcdDisplay->setSecondLine(dots);
  }
  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  lcdDisplay->setFirstLine("WiFi connected");
  lcdDisplay->setSecondLine(WiFi.SSID());
  Serial.println(WiFi.localIP());
}

void setupMQTT()
{
  mqttClientWrapper.init(&devices);
  mqttClientWrapper.reconnect();

  lcdDisplay->setFirstLine("MQTT connected");

  mqttClientWrapper.publishSerialData((char *)"SCHWACH/log", (char *)"SCHWACH connected");
  mqttClientWrapper.subscribe((char *)"manifest/#");
  mqttClientWrapper.publishSerialData((char *)"manifest/broadcast", (char *)"");
}

void setup()
{
  Serial.begin(115200);
  Serial.println("Connecting to WiFi...");

  lcdDisplay = new LcdDisplay();
  lcdDisplay->setFirstLine("    SCHWACH!");
  delay(200);

  mainMenu.init(&lcdDisplay, &devices, &mqttClientWrapper);
  mainMenu.generateMenu();

  input.init(&devices, &mqttClientWrapper);
  input.setMenu(&mainMenu);

  setupWifi();

  setupMQTT();

  mainMenu.printMenu();
}

void loop()
{
  // delay(500);
  if (wifiUpdateInterval > 0)
  {
    wifiUpdateInterval--;
  }
  else
  {
    wifiUpdateInterval = 20000;
    checkWifi();
  }

  // Read keyboard inputs
  input.read();

  mqttClientWrapper.loop();
}
