#ifndef WEMOSWITCH_H
#define WEMOSWITCH_H
// by Amit Kumar

#include <Arduino.h>
#include "Witty.h"
#include "switch.h"
#include "UpnpBroadcastResponder.h"
#include "CallbackFunction.h"
//#include "WebServer.h"
#include "WeMo.h"
#include"Util.h"
//#include "SmartSwitch.h"

class WeMoSwitch
{
private:
  int counter = 10;
  Switch *relaySwitch[WeMo::NoOfRelay];
  UpnpBroadcastResponder upnpBroadcastResponder;
 //Callback function for On/Off
static bool SwitchOn(int );
static bool SwitchOff(int);


 public:
  // Main Functions
  bool initWemoSwitch();
  void wemoSwitchLoop();

 

  //Constructor and Destructor
  WeMoSwitch();
  ~WeMoSwitch();

 

}; //End of Class

#endif
