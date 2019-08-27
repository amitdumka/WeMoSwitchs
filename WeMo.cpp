#include "WeMo.h"

const String WeMo::Activation_Code = "Att01@24";
#ifdef NODEMCU

String WeMo::RelayNames[] = {"Switch 1", "Switch 2", "Switch 3", "Switch 4"};
int WeMo::RelayPins[] = {19, 10, 13, 16};
bool WeMo::isRelayOn[] = {false, false, false, false};

#ifdef RetroSwitch
int WeMo::RelayInputPin[] = {4, 5, 12, 14};
int WeMo::RelayStatus[] = {0, 0, 0, 0};
#endif

#ifdef Alexa
int WeMo::RelayPort[] = {81, 82, 83, 84};
#endif

#endif

#ifdef WITTY

#ifndef RetroSwitch
String WeMo::RelayNames[] = {
    "Switch 1",
    "Switch 2",
    "Switch 3",
}; // "Switch 4"};
int WeMo::RelayStatus[] = {0, 0, 0};
int WeMo::RelayPins[] = {
    0,
    0,
    0,
};
int WeMo::RelayPort[] = {81, 82, 83};
bool WeMo::isRelayOn[] = {false, false, false};
#else
String WeMo::RelayNames[] = {
    "Switch 1",
    "Switch 2"};
int WeMo::RelayStatus[] = {
    0,
    0,
};
int WeMo::RelayPins[] = {

    0,
    0,
};
int WeMo::RelayPort[] = {
    81,
    82,
};
bool WeMo::isRelayOn[] = {false, false};
#endif
#endif

#ifdef ESP32
// Its Better to Hard code here rather then calling function to do , it will save time and memory use and response time will be fast
String WeMo::RelayNames[] = {"Switch 1", "Switch 2", "Switch 3", "Switch 4", "Switch 1", "Switch 2", "Switch 3", "Switch 4"};
int WeMo::RelayPins[] = {0, 0, 0, 0, 0, 0, 0, 0};
bool WeMo::isRelayOn[] = {false, false, false, false, false, false, false, false};
#ifdef RetroSwitch
int WeMo::RelayInputPin[] = {0, 0, 0, 0, 0, 0, 0, 0};
int WeMo::RelayStatus[] = {0, 0, 0, 0, 0, 0, 0, 0};
#endif
#ifdef Alexa
int WeMo::RelayPort[] = {0, 0, 0, 0, 0, 0, 0, 0};
#endif
#endif

//Config

//Change Before Flashing
const char *WeMo::SSID = "AMIT_IOT";
const char *WeMo::password = "12345678";
const char *WeMo::Host = "Amit_IOT";

bool WeMo::wifiConnected = false;

//AP Config  Check is required now.
bool WeMo::isAPOn = false;
bool WeMo::isAPRequired = false;

// Unqiue Id. Can be used to know different devices on network
const double WeMo::Device_Id = 67861;

const String WeMo::AP_Name = "Amit_IOT_" + String(WeMo::Device_Id);

//Change this based on requirement

//Static IP . Check for use if it used or not With WifiManager
const IPAddress WeMo::_IP = IPAddress(192, 168, 5, 1);
const IPAddress WeMo::_GW = IPAddress(192, 168, 5, 1);
const IPAddress WeMo::_SN = IPAddress(255, 255, 255, 0);

// On Off Operation of relay Switches
void WeMo::OperateRelay(int switchIndex, int onOff)
{
    WeMo::isRelayOn[switchIndex] = (onOff == HIGH ? true : false);
    digitalWrite(WeMo::RelayPins[switchIndex], onOff);
    digitalWrite(LED_BUILTIN, LOW);  // Turn the LED on by making the voltage LOW
    delay(1000);                     // Wait for a second
    digitalWrite(LED_BUILTIN, HIGH); // Turn the LED off by making the voltage HIGH
    // Make it perfect
    saveRelayConfiguration(WeMo::RelayNames[switchIndex], onOff, WeMo::RelayNames[switchIndex] + switchIndex, WeMo::isRelayOn[switchIndex]);
}

// Stup PinMode.. Chech of uses and way
void WeMo::SetUpRelaySwitch()
{

    for (int i = 0; i < WeMo::NoOfRelay; i++)
    {
        pinMode(WeMo::RelayPins[i], OUTPUT);
    }
    
    pinMode(WeMo::InBuilt_Led,OUTPUT);//InBuilt LED  D4/02 ESP12
}
#ifdef RetroSwitch
//Setup Input pin mode Check for uses and way
void WeMo::SetUpRetroSwitch()
{
    for (int i = 0; i < WeMo::NoOfSwitch; i++)
    {
        pinMode(WeMo::RelayInputPin[i], INPUT);
    }
}

//Looping . Must be called on Loop() only.
void WeMo::WeMoRetroSwitchLoop()
{
    static int relayReadValue = 0;
    for (int i = 0; i < WeMo::NoOfSwitch; i++)
    {
        relayReadValue = digitalRead(WeMo::RelayInputPin[i]);
        if (relayReadValue != WeMo::RelayStatus[i])
        {
            WeMo::OperateRelay(i, relayReadValue);
            WeMo::RelayStatus[i] = relayReadValue;
            Serial.print(" Switch ");
            Serial.print(i);
            Serial.print(" status changed to ");
            Serial.println(relayReadValue);
        }
    }
}
#endif