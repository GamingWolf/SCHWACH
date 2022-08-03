#include "menu.h"

Menu::Menu(int intId, String strName, String strDescription)
{
    id = intId;
    name = strName;
    description = strDescription;
}

void Menu::init(LcdDisplay **newDisplay, std::vector<Device> *newDevices, MQTTClientWrapper *newMqttClientWrapper)
{
    lcdDisplay = *newDisplay;
    devices = newDevices;
    mqttClientWrapper = newMqttClientWrapper;
}

Menu Menu::getMenu()
{
    return *this;
}

int Menu::getSelectedIndex()
{
    return selectedIndex;
}

int Menu::getId()
{
    return id;
}

String Menu::getName()
{
    return name;
}

String Menu::getDescription()
{
    return description;
}

int Menu::getCurrentFlag()
{
    return currentFlag;
}

void Menu::setSelectedIndex(int newIndex)
{
    selectedIndex = newIndex;
}

void Menu::setSelectedDevice(int newDeviceIndex)
{
    selectedDevice = newDeviceIndex;
}

void Menu::setSelectedDeviceOption(int newDeviceOptionIndex)
{
    selectedDeviceOption = newDeviceOptionIndex;
}

void Menu::setSelectedDeviceOptionChoice(int newDeviceOptionChoiceIndex)
{
    selectedDeviceOptionChoice = newDeviceOptionChoiceIndex;
}

void Menu::generateMenu()
{
    subMenus.push_back(new Menu(0, "Devices", "List of Devices"));
    subMenus.push_back(new Menu(1, "Settings", "SCHWACH Config"));
    subMenus.push_back(new Menu(2, "About", "About SCHWACH"));
    subMenus.push_back(new Menu(3, "Console", "Coming in V2"));
}

void Menu::increaseSelectedIndex()
{
    Device currentDevice = Device("", {});
    std::vector<DeviceOption> currentOptions = {};
    std::vector<DeviceOptionChoice> currentOptionChoices = {};
    if (devices->size() > 0)
    {
        currentDevice = devices->at(selectedDevice);
        currentOptions = currentDevice.getOptions();
        currentOptionChoices = currentOptions.at(selectedDeviceOption).getOptions();
    }
    switch (currentFlag)
    {
    case DEVICE_MENU:
        if (selectedDevice < devices->size() - 1)
        {
            selectedDevice++;
            printDevices();
        }
        break;
    case DEVICE_OPTION_MENU:
        if (selectedDeviceOption < currentOptions.size() - 1)
        {
            selectedDeviceOption++;
            printDeviceOptions();
        }
        break;
    case DEVICE_OPTION_CHOICE:

        if (selectedDeviceOptionChoice < currentOptionChoices.size() - 1)
        {
            selectedDeviceOptionChoice++;
            printDeviceOptionsSelection();
        }
        break;
    case MAIN_MENU:
    case SETTINGS_MENU:
    case ABOUT_MENU:
    case CONSOLE_MENU:
        if (selectedIndex < subMenus.size() - 1)
        {
            selectedIndex++;
            printMenu();
        }
        break;
    default:
        break;
    }
}

void Menu::decreaseSelectedIndex()
{
    switch (currentFlag)
    {
    case DEVICE_MENU:
        if (selectedDevice > 0)
        {
            selectedDevice--;
            printDevices();
        }
        break;
    case DEVICE_OPTION_MENU:
        if (selectedDeviceOption > 0)
        {
            selectedDeviceOption--;
            printDeviceOptions();
        }
        break;
    case DEVICE_OPTION_CHOICE:
        if (selectedDeviceOptionChoice > 0)
        {
            selectedDeviceOptionChoice--;
            printDeviceOptionsSelection();
        }
        break;
    case MAIN_MENU:
    case SETTINGS_MENU:
    case ABOUT_MENU:
    case CONSOLE_MENU:
        if (selectedIndex > 0)
        {
            selectedIndex--;
            printMenu();
        }
        break;
    default:
        break;
    }
}

void Menu::printMenu()
{
    Serial.println("Printing menu");
    inDeviceList = false;
    inDevice = false;
    inOptionChoice = false;
    String firstMenuLine, secondMenuLine = "";
    for (int i = 0; i < subMenus.size(); i++)
    {
        if (firstMenuLine.length() >= 16 && i <= selectedIndex)
        {
            firstMenuLine = "";
        }
        else if (firstMenuLine.length() >= 16)
        {
            break;
        }

        if (i == selectedIndex)
        {
            firstMenuLine += ">";
            secondMenuLine += subMenus[i]->getDescription();
        }
        else
        {
            firstMenuLine += "";
        }

        firstMenuLine += subMenus[i]->getName();
        firstMenuLine += " ";
    }

    lcdDisplay->setFirstLine(firstMenuLine);
    lcdDisplay->setSecondLine(secondMenuLine);
    currentFlag = MAIN_MENU;
}

void Menu::printDevices()
{
    Serial.println("Printing devices");
    String firstMenuLine, secondMenuLine = "";
    inDeviceList = true;
    inDevice = false;
    inOptionChoice = false;
    for (int i = 0; i < devices->size(); i++)
    {
        if (firstMenuLine.length() >= 16 && i <= selectedDevice)
        {
            firstMenuLine = "";
        }
        else if (firstMenuLine.length() >= 16)
        {
            break;
        }

        if (i == selectedDevice)
        {
            if (firstMenuLine.length() + devices->at(i).getName().length() >= 16)
            {
                firstMenuLine = "";
            }

            firstMenuLine += ">";
            int numberOfOptions = devices->at(i).getOptions().size();
            secondMenuLine += "Has " + String(numberOfOptions) + " options";
        }
        else
        {
            firstMenuLine += "";
        }

        firstMenuLine += devices->at(i).getName();
        firstMenuLine += " ";
    }

    lcdDisplay->setFirstLine(firstMenuLine);
    lcdDisplay->setSecondLine(secondMenuLine);

    currentFlag = DEVICE_MENU;
}

void Menu::printDeviceOptions()
{
    Serial.println("Printing device options");
    String firstMenuLine, secondMenuLine = "";
    auto deviceOptions = devices->at(selectedDevice).getOptions();
    Serial.println(deviceOptions.size());
    inDevice = true;
    inOptionChoice = false;
    for (int i = 0; i < deviceOptions.size(); i++)
    {
        if (firstMenuLine.length() >= 16 && i <= selectedDeviceOption)
        {
            firstMenuLine = "";
        }
        else if (firstMenuLine.length() >= 16)
        {
            break;
        }

        auto optionName = devices->at(selectedDevice).getOptions().at(i).getName();

        if (i == selectedDeviceOption)
        {
            if (firstMenuLine.length() + optionName.length() >= 16)
            {
                firstMenuLine = "";
            }

            firstMenuLine += ">";
            secondMenuLine += deviceOptions.at(i).getDescription();
        }
        else
        {
            firstMenuLine += "";
        }

        firstMenuLine += optionName;
        firstMenuLine += " ";
    }

    lcdDisplay->setFirstLine(firstMenuLine);
    lcdDisplay->setSecondLine(secondMenuLine);

    currentFlag = DEVICE_OPTION_MENU;
}

void Menu::printDeviceOptionsSelection()
{
    Serial.println("Printing device option selection");
    String firstMenuLine, secondMenuLine = "";
    auto deviceOptions = devices->at(selectedDevice).getOptions();
    auto deviceOptionChoices = deviceOptions.at(selectedDeviceOption).getOptions();
    firstMenuLine += deviceOptions.at(selectedDeviceOption).getName();
    inOptionChoice = true;
    for (int i = 0; i < deviceOptionChoices.size(); i++)
    {
        if (secondMenuLine.length() >= 16 && i <= selectedDeviceOptionChoice)
        {
            secondMenuLine = "";
        }
        else if (secondMenuLine.length() >= 16)
        {
            break;
        }

        if (i == selectedDeviceOptionChoice)
        {
            if (secondMenuLine.length() + deviceOptionChoices.at(i).getName().length() >= 16)
            {
                secondMenuLine = "";
            }
            secondMenuLine += ">";
        }
        else
        {
            secondMenuLine += "";
        }

        secondMenuLine += deviceOptionChoices.at(i).getName();
        secondMenuLine += " ";
    }

    lcdDisplay->setFirstLine(firstMenuLine);
    lcdDisplay->setSecondLine(secondMenuLine);

    currentFlag = DEVICE_OPTION_CHOICE;
}

void Menu::printSubMenu(int index)
{
    switch (index)
    {
    case DEVICE_MENU:
        if (devices->size() == 0)
        {
            lcdDisplay->setFirstLine("Attention: ");
            lcdDisplay->setSecondLine("No devices found");
            delay(1500);
            printMenu();
            break;
        }
        if (inDeviceList)
        {
            printSubMenu(DEVICE_OPTION_MENU);
        }
        else
        {
            printDevices();
        }
        break;
    case SETTINGS_MENU:
        lcdDisplay->setFirstLine("Settings");
        lcdDisplay->setSecondLine("Coming soon");
        delay(1500);
        printMenu();
        currentFlag = SETTINGS_MENU;
        break;

    case ABOUT_MENU:
        lcdDisplay->setFirstLine("SCHWACH v1.1");
        lcdDisplay->setSecondLine("Hit b to go back");
        currentFlag = ABOUT_MENU;
        break;
    case CONSOLE_MENU:
        lcdDisplay->setFirstLine("Console");
        lcdDisplay->setSecondLine("Coming soon");
        delay(1500);
        currentFlag = CONSOLE_MENU;
        printMenu();
        break;
    case DEVICE_OPTION_MENU:
        if (inDevice)
        {
            printSubMenu(DEVICE_OPTION_CHOICE);
        }
        else
        {
            printDeviceOptions();
        }
        break;
    case DEVICE_OPTION_CHOICE:
        if (inOptionChoice)
        {
            executeChoice();
        }
        else
        {
            printDeviceOptionsSelection();
        }

        break;
    default:
        break;
    }
}

void Menu::executeChoice()
{
    auto deviceOptions = devices->at(selectedDevice).getOptions();
    auto deviceOptionChoices = deviceOptions.at(selectedDeviceOption).getOptions();

    auto optionType = deviceOptions.at(selectedDeviceOption).getType();
    auto topicName = deviceOptions.at(selectedDeviceOption).getTopicName();
    auto deviceName = devices->at(selectedDevice).getName();
    auto topic = String(deviceName + "/" + topicName);
    char *cTopic = new char[topic.length() + 1];
    strcpy(cTopic, topic.c_str());

    auto choiceValue = deviceOptionChoices.at(selectedDeviceOptionChoice).getValue();
    auto choiceName = deviceOptionChoices.at(selectedDeviceOptionChoice).getName();
    auto choice = "{\"data\":\"" + choiceValue + "\"}";
    char *cChoice = new char[choice.length() + 1];
    strcpy(cChoice, choice.c_str());

    if (optionType.equals("publish"))
    {
        mqttClientWrapper->publishSerialData(cTopic, cChoice);
        // mqttClientWrapper->publishSerialData((char *)"HATER/togglePower", (char *)"on");
        lcdDisplay->setFirstLine("Published: " + choiceName + " to");
        lcdDisplay->setSecondLine(topic);
        delay(1500);
        printDeviceOptions();
    }
    else if (optionType.equals("subscribe"))
    {
        mqttClientWrapper->subscribe(cTopic);
        lcdDisplay->setFirstLine("Subscribed to: ");
        lcdDisplay->setSecondLine(cTopic);
        delay(1500);
        printDeviceOptions();
    }
}

void Menu::padTo(std::string &str, const size_t num, const char paddingChar)
{
    if (num > str.size())
        str.insert(str.size(), num - str.size(), paddingChar);
}