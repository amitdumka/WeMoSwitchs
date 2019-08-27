#ifndef WEMO_H
#define WEMO_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "Util.h"
#include "Config.h"

class WeMo
{
public:
  static const double Device_Id;
  static const String Activation_Code;

#ifdef NODEMCU
  static const int NoOfRelay = 4; // Change based on project
#ifdef RetroSwitch
  static const int NoOfSwitch = 4; // Change based on project
#endif
#endif

#ifdef ESP32
  static const int NoOfRelay = 8; // Change based on project
#ifdef RetroSwitch
  static const int NoOfSwitch = 8; // Change based on project
#endif
#endif

#ifdef WITTY
#ifdef RetroSwitch
  static const int NoOfRelay = 2;  // Change based on project
  static const int NoOfSwitch = 2; // Change based on project
#else
  static const int NoOfRelay = 3; // Change based on project
#endif
#endif

#ifdef RetroSwitch
  static int RelayInputPin[]; //input pin for retrofitting swicthes
  static int RelayStatus[];   //need to check if Any use is there
#endif

  static int RelayPins[];
  static String RelayNames[];
  static bool isRelayOn[];
#ifdef Alexa
  static int RelayPort[]; //For Alexa Support;
#endif
  //Use both Inbuilt led
  static const int InBuilt_Led = D4; // Led at esp 12 chip  and Inbuilt nodemcu is at D0 or gpio 16

  static const char *SSID;
  static const char *password;
  static const char *Host;

  static const WiFiMode_t WiFiMode = WIFI_STA;

  static const int WebServerHTTP_Port = 80;
  static const int WebServerHTTPS_Port = 443;

#ifdef Alexa
  static const int StartPort = 81;
  static const int LastPort = 90; //Max Switch /Replay can be handle by Alexa WeMos
#endif
  static bool isAPOn;
  static bool isAPRequired;
  static const String AP_Name;

  static bool wifiConnected;

  //start-block2
  static const IPAddress _IP;
  static const IPAddress _GW;
  static const IPAddress _SN;

  static void OperateRelay(int switchIndex, int onOff);
  static void SetUpRelaySwitch();

#ifdef RetroSwitch
  //Retrofitting switches
  static void SetUpRetroSwitch();
  static void WeMoRetroSwitchLoop();
#endif
};

#endif
