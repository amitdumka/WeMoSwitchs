#ifndef WITTY_H
#define WITTY_H
#include <functional>

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiUDP.h>

#include "CallbackFunction.h"
// By Amit Kumar

class Witty
{
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

  const char *ssid = "AmitKr";
  const char *password = "12345678";

  const char *host = "Amit_IOT";
  static bool wifiConnected;
  bool connectWifi();

  void InitWitty();
  void SetLedDigital(int r, int g, int b);

  void SetLedAnalog(int r, int g, int b);
  bool setLedColor(int r, int g, int b);

  int isButtonPressed();
  bool HandelButton(CallbackFunction cb);
  bool ResetDevice();
  bool ReconnectWifi();
};

#endif
