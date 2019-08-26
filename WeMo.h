#ifndef WEMO_H
#define WEMO_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "Util.h"

//By Default WeMo will be NodeMcu mode. you can change either by function or you can hard code . as most of code is fixed. 
// You can add Temp and humdity module based on board selected.
//There Will be sensor section Which need to be activated. Wait for Version 2.0

class WeMo
{
public:
  static const double Device_Id;
  static const String Activation_Code;

  static  int NoOfRelay; //= 4;  // Change based on project
  static  int NoOfSwitch;// =4; // Change based on project

  static int RelayInputPin[]; //input pin for retrofitting swicthes
  static int RelayStatus[];   //need to check if Any use is there

  static int RelayPins[];
  static String RelayNames[];
  static bool isRelayOn[];

  static int RelayPort[]; //For Alexa Support;

  //Use both Inbuilt led
  static const int InBuilt_Led = D4; // Led at esp 12 chip  and Inbuilt nodemcu is at D0 or gpio 16

  static const char *SSID;
  static const char *password;
  static const char *Host;

  static const WiFiMode_t WiFiMode = WIFI_STA;

  static const int WebServerHTTP_Port = 80;
  static const int WebServerHTTPS_Port = 443;

  static const int StartPort = 81;
  static const int LastPort = 90; //Max Switch /Replay can be handle by Alexa WeMos

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
  static void SetUpRetroSwitch();
  //Retrofitting switches
  static void WeMoRetroSwitchLoop();
};

#endif
