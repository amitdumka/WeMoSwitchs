#ifndef WITTY_H
#define WITTY_H
#include "WeMo.h"
#include <functional>

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiUDP.h>

#include <WiFiManager.h>

#include "CallbackFunction.h"
#include "Util.h"
// By Amit Kumar

class Witty
{

private:
  //Witty Cloud Config Move back to Witty Class
  static const int BUTTON = 4;    // Define pin the button is connected to   // This button pin can be overridden
  static const int LDR = A0;      // Define the analog pin the LDR is connected to
  static const int RedLed = D8;   //15   //Led pin can be over ridden , led can be used for status of pin
  static const int GreenLed = D6; //12
  static const int BlueLed = D7;  //13

  static const int Pin14 = 14; // Suitable name can be given to these pin or can be used with define
  static const int Pin16 = 16;
  static const int Pin5 = 5;

  static const int UsablePinCount = 3; // Check if required other wise it can be removed or commented

public:
  static int btn_Status;

  void InitWitty();
  void InitWitty(bool isConnected);
  void InitWitty(bool isConnected, bool isConfiged);
  void SetLedDigital(int r, int g, int b);
  void SetLedAnalog(int r, int g, int b);
  bool setLedColor(int r, int g, int b);
  int isButtonPressed();
  bool HandelButton(CallbackFunction cb);
  bool ResetDevice();
  bool ReconnectWifi();
  void LedStatus(bool isConnecte);
};

#endif
