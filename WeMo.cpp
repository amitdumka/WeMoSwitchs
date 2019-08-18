#include "WeMo.h"

const String WeMo::Activation_Code = "Att01@24";

//Change Before Flashing
const char *WeMo::SSID = "AmitKr";
const char *WeMo::password = "12345678";
const char *WeMo::Host = "Amit_IOT";

const double WeMo::Device_Id = 67861;
//Change this based on requirement

String WeMo::RelayNames[] = {"Switch 1", "Switch 2", "Switch 3", "Switch 4"};
int WeMo::RelayStatus[] = {0, 0, 0, 0};
int WeMo::RelayPins[] = {14, 15, 03, 01};
int WeMo::RelayPort[] = {81, 82, 83, 84};
bool WeMo::isRelayOn[NoOfRelay] = {false, false, false, false};

// void WeMo::Config()
