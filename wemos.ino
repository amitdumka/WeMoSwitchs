/*
   Four Channel Relayed Based on wemos switches
   By: Amit Kumar (2019)
*/
#include "WeMo.h"
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
#include <functional>
#include "switch.h"
#include "UpnpBroadcastResponder.h"
#include "CallbackFunction.h"
#include "Witty.h"
#include "WeMoSwitch.h"
#include "WebServer.h"
#include "Util.h"
//#include <SD.h>
#include <SPI.h>

Witty wittyB;
WeMoSwitch *weMo;
WebServer *webServer;
static const double DeviceId = 5458979879;

void setup()
{
  Serial.begin(9600);
  //Load Config File
  if (!ReadConfigFile())
  { //SaVe ConfigFile
    saveConfiguration();
  }
  //PrintConfig();
  printFile(ConfigFileName.c_str());
  wittyB.InitWitty(false);
  weMo = new WeMoSwitch(wittyB);
  Serial.println("Witty Board Init  done");
  webServer = new WebServer(80);
  webServer->StartWebServer();
  weMo->initWemoSwitch();
  Serial.println("Wemos Switch init done");
  if (MDNS.begin("amitiot"))
  {
    Serial.println("MDNS responder started: amitiot");
    // Add service to MDNS-SD
    MDNS.addService("http", "tcp", 80);
  }
} // end of Setup

void loop()
{
  MDNS.update();
  webServer->IndexPage(); // WebServer
  weMo->wemoSwitchLoop();
  if (wittyB.isButtonPressed() == LOW)
  {
    Serial.println("Button is pressed...");
    delay(200);
    Serial.println("Reseting device....");
    wittyB.ResetDevice();
    delay(200);
  }
}
