/*
   Four Channel Relayed Based on wemos switches
   By: Amit Kumar (2019)
*/
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
#include <functional>
#include "switch.h"
#include "UpnpBroadcastResponder.h"
#include "CallbackFunction.h"
#include "witty.h"
#include "wemoswitch.h"
#include "WebServer.h"



Witty wittyB;

WeMoSwitch *weMo;
WebServer *webServer;




void setup()
{
  Serial.begin(9600);
  wittyB.InitWitty();
  weMo= new WeMoSwitch(wittyB);
  Serial.println("Witty Board Init  done");
  webServer= new WebServer(80);
  webServer->StartWebServer();
  weMo->initWemoSwitch();
 
  Serial.println("Wemos Switch init done");
  if (MDNS.begin("amitiot")) {
    Serial.println("MDNS responder started: amitiot");
    // Add service to MDNS-SD
  MDNS.addService("http", "tcp", 80);
  }


}// end of Setup

void loop()
{
   MDNS.update();
 // WiFiClient client = webServer->server->available(); // Listen for incoming clients
    webServer->RootDoc();
  weMo->wemoSwitchLoop();
  if(wittyB.isButtonPressed()==LOW)
  {
    Serial.println("Button is pressed...");
    delay(200);
    Serial.println("Reconnecting Wifi....");
    wittyB.ReconnectWifi();
    delay(200);
    //TODO: where first need to delete the ref then call init function
    Serial.println("Reconnecting Switch....");
    delete weMo;
    if(weMo==NULL)
      weMo= new WeMoSwitch(wittyB);
    weMo->initWemoSwitch();
    
    //delay(2000);
   
  }
}



// connect to wifi – returns true if successful or false if not
