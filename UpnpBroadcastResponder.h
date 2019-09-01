#ifndef UPNPBROADCASTRESPONDER_H
#define UPNPBROADCASTRESPONDER_H
 
#include "Config.h"

#include <Arduino.h>
#ifdef NODEMCU
#include <ESP8266WiFi.h>
#endif
#include <WiFiUDP.h>
#include "Switch.h"

class UpnpBroadcastResponder {
private:
        WiFiUDP UDP;  
public:
        UpnpBroadcastResponder();
        ~UpnpBroadcastResponder();
        bool beginUdpMulticast();
        void serverLoop();
        void addDevice(Switch& device);
};
 
#endif
