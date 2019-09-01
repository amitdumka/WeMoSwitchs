#ifndef UTIL_H
#define UTIL_H

#include <FS.h> //this needs to be first, or it all crashes and burns...
#include <ArduinoJson.h> //https://github.com/bblanchon/ArduinoJson
#include <ESP8266WiFi.h> //https://github.com/esp8266/Arduino
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include "WeMo.h"


 const String ConfigFileName = "/config.json";

bool CallWiFiManager(bool isNew);
bool ReadConfigFile();
bool saveConfiguration();
void printFile(const char *filename);
bool saveRelayConfiguration(String sName, int value, String sName2, bool value2);

#endif