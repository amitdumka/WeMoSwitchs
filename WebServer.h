#ifndef WEBSERVER_H
#define WEBSERVER_H
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ArduinoOTA.h>
#include <ESP8266WiFi.h>
#include <Arduino.h>
#include "WeMo.h"

class WebServer
{

private:
  int WebPort = 80;
  int WebSecurePort = 443;
  
  //Check onwards
  String header;
  // Current time
  unsigned long currentTime = millis();
  // Previous time
  unsigned long previousTime = 0;
  // Define timeout time in milliseconds (example: 2000ms = 2s)
  static const long timeoutTime; // = 2000;
  
  void AddButton(String switchName, bool outputState, int index, WiFiClient client);
  void ButtonSelect();
  void EndDoc(WiFiClient client);
  void WebBody(WiFiClient client);

public:
  WiFiServer *server = NULL;
  bool StartWebServer();
  WebServer();
  WebServer(int port);
  void RootDoc(WiFiClient client);
  void IndexPage();
};
#endif
