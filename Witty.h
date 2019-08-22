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
  
public:
  
   static int btn_Status;

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
