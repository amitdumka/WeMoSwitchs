#ifndef WEBSERVER_H
#define WEBSERVER_H
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ArduinoOTA.h>
//#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <Arduino.h>

class WebServer
{

private:
  int WebPort = 80;
  int WebSecurePort = 443;
  
  //Check onwards
  String header;
  // Auxiliar variables to store the current output state
  String output1State = "off";
  String output2State = "off";
  String output3State = "off";
  String output4State = "off";

  // Assign output variables to GPIO pins
  static const int output1; //= 5;
  static const int output2; //= 4;
  static const int output3; //= 5;
  static const int output4; //= 4;

  // Current time
  unsigned long currentTime = millis();
  // Previous time
  unsigned long previousTime = 0;
  // Define timeout time in milliseconds (example: 2000ms = 2s)
  static const long timeoutTime; // = 2000;
  
  void AddButton(String switchName, String outputState, int index, WiFiClient client);
  void ButtonSelect();
  void EndDoc(WiFiClient client);
  void WebBody(WiFiClient client);

public:
  WiFiServer *server = NULL;
  bool StartWebServer();
  WebServer();
  WebServer(int port);
  void RootDoc(WiFiClient client);
  void OperateRelay(int switchIndex, int onOff);
  void IndexPage();
};
#endif
