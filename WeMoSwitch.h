#ifndef WEMOSWITCH_H
#define WEMOSWITCH_H
// by Amit Kumar

#include <Arduino.h>
#include "Witty.h"
#include "switch.h"
#include "UpnpBroadcastResponder.h"
#include "CallbackFunction.h"
#include "WebServer.h"
#include "WeMo.h"
//#include "SmartSwitch.h"

class WeMoSwitch
{
private:
  //boolean wifiConnected = false;
  int counter = 10;

  Witty wittyB;
  // Set Relay Pins
  // int relayOnePin = 14;
  // int relayTwoPin = 15;
  // int relayThreePin = 03;
  // int relayFourPin = 01;

  
public:

  Switch *relaySwitch[WeMo::NoOfRelay];
  UpnpBroadcastResponder upnpBroadcastResponder;

  // Main Functions
  bool initWemoSwitch();
  void wemoSwitchLoop();

  //Constructor and Destructor
  WeMoSwitch(Witty b);
  ~WeMoSwitch();

  //Callback function for On/Off
static bool SwitchOn(int );
static bool SwitchOff(int);



}; //End of Class

#endif
