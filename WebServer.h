#ifndef WEBSERVER_H
#define WEBSERVER_H
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ArduinoOTA.h>
//#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <Arduino.h>

class WebServer {

  private:
    bool LoggedIn = false;
    int WebPort = 80;
    int WebSecurePort = 443;
    const char* www_username = "admin";
    const char* www_password = "1234";
    // allows you to set the realm of authentication Default:"Login Required"
    const char* www_realm = "Custom Auth Realm";
    // the Content of the HTML response in case of Unautherized Access Default:empty
    String authFailResponse = "Authentication Failed";
    void handleAuth(const char  *www_username, const char *www_password);

    //Check onwards
    String header;
    // Auxiliar variables to store the current output state
    String output1State = "off";
    String output2State = "off";
    String output3State = "off";
    String output4State = "off";

    // Assign output variables to GPIO pins
    static const int output1 ;//= 5;
    static const int output2 ;//= 4;
    static const int output3 ;//= 5;
    static const int output4 ;//= 4;
    
    // Current time
    unsigned long currentTime = millis();
    // Previous time
    unsigned long previousTime = 0;
    // Define timeout time in milliseconds (example: 2000ms = 2s)
    static const long timeoutTime;// = 2000;


  public:
    WiFiServer *server = NULL;
    bool StartWebServer();
    void ServerLoop();
    WebServer();
    WebServer(int port);
    void Send(int r, char *type, char *data);
    void Send(int r, char *type, String data);
    bool isLoggedIn();

    void RootDoc(WiFiClient client);
    void RootDoc();


};
#endif
