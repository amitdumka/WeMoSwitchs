#ifndef WEMO_H
#define WEMO_H
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "Util.h"



class WeMo
{
public:
    static const double Device_Id;
    static const String Activation_Code;

    static const int NoOfRelay = 4;

    static int RelayInputPin[NoOfRelay]; //input pin for retrofitting swicthes
    static int RelayStatus[NoOfRelay]; //need to check if Any use is there
    
    static int RelayPins[NoOfRelay];
    static String RelayNames[NoOfRelay];
    static bool isRelayOn[NoOfRelay];
    
    static int RelayPort[NoOfRelay]; //For Alexa Support;

    //Witty Cloud Config Move back to Witty Class
    static const int BUTTON = 4; // Define pin the button is connected to
    static const int LDR = A0;   // Define the analog pin the LDR is connected to
    static const int RedLed = D8;
    static const int GreenLed = D6;
    static const int BlueLed = D7;

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
