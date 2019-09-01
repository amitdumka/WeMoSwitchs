#ifndef WEMO_MAIN_H
#define WEMO_MAIN_H

#include "WeMo.h"
#include <functional>
#include "Util.h"
#include "Config.h"

#ifdef MQTT
//#include "mqttserver.h"
#include "Async_MQTT_Server.h"
#endif

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

class WeMo_Main
{
private:

public:
    void CallInSetUp();
    void CallInLoop();
};

#endif

void WeMo_Main::CallInSetUp()
{
#ifdef CONFIG_DATA
    WeMo::ProcessProcessConfigData();
#endif

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

    WeMo::SetUpRelaySwitch(); // If Board based Setup is not called then it should be called

#ifdef RetroSwitch
    WeMo::SetUpRetroSwitch();
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
        MDNS.addService("http", "tcp", 80);         // Add service to MDNS-SD
    }

    Serial.println(ESP.getChipId());
    Serial1.println(ESP.getFlashChipId());
    Serial.println(ESP8266_CLOCK);
}

void WeMo_Main::CallInLoop()
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

#ifdef RetroSwitch
    WeMo::WeMoRetroSwitchLoop();
#endif

#ifdef WITTY
    wittyB.ButtonLoop();
#endif
}