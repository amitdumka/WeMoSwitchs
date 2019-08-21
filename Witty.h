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
  //WiFiManager wifiManager;

public:
  static const int BUTTON_PIN; // Define pin the button is connected to
  static const int LDR_PIN;    // Define the analog pin the LDR is connected to
  static const int RedLed;
  static const int GreenLed;
  static const int BlueLed;

  static int btn_Status;

  //Wifi Connection

  // Change this before you flash
  //TODO: making then can set by web page , api or app

  static bool wifiConnected;

  bool connectWifi();
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
