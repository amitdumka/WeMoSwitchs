#ifndef WEMOSWITCH_H
#define WEMOSWITCH_H
// by Amit Kumar

#include <Arduino.h>
#include"Witty.h"
#include "switch.h"
#include "UpnpBroadcastResponder.h"
#include "CallbackFunction.h"
#include "WebServer.h"

class WeMoSwitch
{
  private:

    boolean wifiConnected = false;
    int counter=10;

    Witty wittyB;
    WebServer webServer;

    // Set Relay Pins
    int relayOnePin = 14;
    int relayTwoPin = 15;
    int relayThreePin = 03;
    int relayFourPin = 01;




    static bool isRelayOneOn ;
    static  bool isRelayTwoOn ;
    static  bool isRelayThreeOn ;
    static  bool isRelayFourOn ;

    // Alising for Switches name which can be set by User through App
    const char *RelayNameOne = "SwitchOne";
    const char *RelayNameTwo = "SwitchTwo";
    const char *RelayNameThree = "SwitchThee";
    const char *RelayNameFour = "SwithcFour";
    
    // function for alising
    char *ReadRelayName(int index);
    bool SetRelayName(int index, char *relayName);


  public:

    Switch *relayOne = NULL;
    Switch *relayTwo = NULL;
    Switch *relayThree = NULL;
    Switch *relayFour = NULL;


    UpnpBroadcastResponder upnpBroadcastResponder;

    // Main Functions
    bool initWemoSwitch();
    bool wemoSwitchLoop();
    void WebLoop();

    //Constructor and Destructor
    WeMoSwitch(); 
    WeMoSwitch(Witty b);
    WeMoSwitch(Witty b, WebServer s);
    WeMoSwitch(bool con);
    ~WeMoSwitch();

    //Callback function for On/Off
    
    static bool SwitchOneOn();
    static bool SwitchOneOff();
    
    static bool SwitchTwoOn();
    static bool SwitchTwoOff();
    
    static bool SwitchThreeOn();
    static bool SwitchThreeOff();
    
    static bool SwitchFourOn();
    static bool SwitchFourOff();

void handleON();
void handleOFF();
void handleRoot();



};//End of Class
















#endif
