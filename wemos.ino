/*
   Four Channel Relayed Based on wemos switches
   By: Amit Kumar (2019)
   Version 1.0
*/

#include "WeMo.h"
#include <functional>
#include "Util.h"

//Config Here

#define WEBSERVER ;   // WebServer.. Give basic web interface to on Off
#define WITTY ;    //Witty Cloud board  very just 3 pin for input or output . good for sensor module
#define ESP32 ;   // ESP32 Boad dev kit rev1
#define NODEMCU ;  // Esp8266  or nodemcu board
#define Alexa ;  // WeMo Switch support with Alexa ( Will Be working for google and other)
#define RetroSwitch;  // To be Used with old/ exisiting wiring
#define MQTT; // Enbaling MQTT
#define WEBAPI; // Enabling WebApi to control Switches and board .. In version 2.0

// Config ends here

#ifdef WEBSERVER
#include "WebServer.h"
#endif
#ifdef WITTY
#include "Witty.h"
#endif
#ifdef Alexa
#include "WeMoSwitch.h"
#endif

#ifdef NODEMCU
#include "WeMo_NodeMcu.h"
#endif
#ifdef ESP32
#include "WeMo_ESP32.h"
#endif

#ifdef NODEMCU
WeMo_NodeMCU nodeMcuB;
#endif

#ifdef ESP32 
WeMo_ESP32 esp32B;
#endif

#ifdef WITTY
Witty wittyB;
#endif
#ifdef Alexa
WeMoSwitch *weMo;
#endif
#ifdef WEBSERVER
WebServer *webServer;
#endif
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


#ifdef NODEMCU
nodeMcuB.Setup();
#endif  
#ifdef ESP32
esp32B.Setup();
#endif

#ifdef WITTY
  wittyB.InitWitty(false);
  Serial.println("Witty Board Init  done");
#endif

#ifdef Alexa
  weMo = new WeMoSwitch();
  Serial.println("WeMoSwtich with Alex added");
  weMo->initWemoSwitch();
  Serial.println("Wemos Switch init done");
#endif

#ifdef WEBSERVER
  webServer = new WebServer(80);
  webServer->StartWebServer();
#endif
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
#ifdef NODEMCU
nodeMcuB.Loop();
#endif  
#ifdef ESP32
esp32B.Loop();
#endif

#ifdef WEBSERVER
  webServer->IndexPage(); // WebServer
#endif
#ifdef Alexa
  weMo->wemoSwitchLoop();
#endif

#ifdef WITTY
// When Inbuilt flash Button is pressed , It will trigger Esp reset
  if (wittyB.isButtonPressed() == LOW)
  {
    Serial.println("Button is pressed...");
    delay(200);
    Serial.println("Reseting device....");
    wittyB.ResetDevice();
    delay(200);
  }
#endif
}
