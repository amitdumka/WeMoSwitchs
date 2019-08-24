/*
   Four Channel Relayed Based on wemos switches
   By: Amit Kumar (2019)
*/
#include "WeMo.h"
#include <functional>
#include "Witty.h"
#include "WeMoSwitch.h"
#include "WebServer.h"
#include "Util.h"

Witty wittyB;
WeMoSwitch *weMo;
WebServer *webServer;
static const double DeviceId = 5458979879;

void setup()
{
  Serial.begin(115200); // Can be increase based on board

  //Load Config File
  if (!ReadConfigFile())
  { //SaVe ConfigFile
    saveConfiguration();
    Serial.println("Saving Config File for first run");
  }
  
  wittyB.InitWitty(false);
  weMo = new WeMoSwitch();
  Serial.println("Witty Board Init  done");
  
  weMo->initWemoSwitch();
  Serial.println("Wemos Switch init done");
  webServer = new WebServer(80);
  webServer->StartWebServer();
  
  if (MDNS.begin("amitiot"))
  {
    Serial.println("MDNS responder started: amitiot");
    // Add service to MDNS-SD
    MDNS.addService("http", "tcp", 80);
  }
  

  Serial.println(ESP.getChipId());
  Serial1.println(ESP.getFlashChipId());
  Serial.println(ESP8266_CLOCK);
  
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
