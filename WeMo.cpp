#include "WeMo.h"

const String WeMo::Activation_Code = "Att01@24";

//Change Before Flashing
const char *WeMo::SSID = "AmitKr";
const char *WeMo::password = "12345678";
const char *WeMo::Host = "Amit_IOT";

bool WeMo::wifiConnected=false;

bool WeMo::isAPOn = false;
bool WeMo::isAPRequired = false;

const double WeMo::Device_Id = 67861;

const String WeMo::AP_Name = "Amit_IOT_" + String( WeMo::Device_Id);
//Change this based on requirement

String WeMo::RelayNames[] = {"Switch 1", "Switch 2", "Switch 3", "Switch 4"};
int WeMo::RelayStatus[] = {0, 0, 0, 0};
int WeMo::RelayPins[] = {14, 15, 03, 01};
int WeMo::RelayPort[] = {81, 82, 83, 84};
bool WeMo::isRelayOn[NoOfRelay] = {false, false, false, false};

//start-block2
const IPAddress WeMo::_IP = IPAddress(192, 168, 5, 1);
const IPAddress WeMo::_GW = IPAddress(192, 168, 5, 1);
const IPAddress WeMo::_SN = IPAddress(255, 255, 255, 0);

void WeMo::OperateRelay(int switchIndex, int onOff)
{
    WeMo::isRelayOn[switchIndex] = (onOff == HIGH ? true : false);
    digitalWrite(WeMo::RelayPins[switchIndex], onOff);
    digitalWrite(LED_BUILTIN, LOW);  // Turn the LED on by making the voltage LOW
    delay(1000);                     // Wait for a second
    digitalWrite(LED_BUILTIN, HIGH); // Turn the LED off by making the voltage HIGH
}
