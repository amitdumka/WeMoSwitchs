#ifndef WEMO_NODEMCU_H
#define WEMO_NODEMCU_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "Config.h"

class WeMo_NodeMCU
{
private:
    //output pin d1 d2 d5 d6 d7   [D8]
    //input  d1 d2 d5  d6 d7  [d0]

    //Final Input Pin Will Be  10, 9, 16, 13
    //Final Output Pin Will Be 5, 4, 14, 12

    static const int MaxInputPin = 4;   
    static const int MaxOutPutPin = 4;

    static int InputSwitchList[MaxInputPin]; 
    static int RelayPinList[MaxOutPutPin];   

public:
    void Setup();
    void Loop();
};

#endif

//Move to CPP file
// int outputPin[4]={9,10,13,16};
//int inputpin[4]={4,5,12,14};

int WeMo_NodeMCU::InputSwitchList[MaxInputPin] = {4, 5, 12, 14};
int WeMo_NodeMCU::RelayPinList[MaxOutPutPin] = {9, 10, 13, 16};

void WeMo_NodeMCU::Setup()
{
    // Assining values to WeMo Config. and Making all variable static data to static
    //These data can be used to restore data in the event of crashing or errors.

    // Pin config
    for(int i=0 ; i<MaxOutPutPin;i++){
        WeMo::RelayPins[i]=RelayPinList[i];
        WeMo::RelayInputPin[i]=InputSwitchList[i];
        pinMode(InputSwitchList[i], INPUT);
        pinMode(RelayPinList[i], OUTPUT);
    }
 
}

void WeMo_NodeMCU::Loop()
{
    // TODO: Check What else code can be written . 
    //Any NodeMCU based code be added here. 
}