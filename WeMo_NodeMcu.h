#ifndef WEMO_NODEMCU_H
#define WEMO_NODEMCU_H

#include <Arduino.h>
#include <ESP8266WiFi.h>

class WeMo_NodeMCU
{
private:
    //output pin d1 d2 d5 d6 d7   [D8]
    //input  d1 d2 d5  d6 d7  [d0]

    //Final Input Pin Will Be  10, 9, 16, 13
    //Final Output Pin Will Be 5, 4, 14, 12

    static const int MaxInputPin = 4;
    static const int MaxOutPutPin = 4;

    static int InputSwitchList[MaxInputPin]; //={34,35,35,39,27,16,17,12};
    static int RelayPinList[MaxOutPutPin];   //=   {32,33,25,26,21,22,04,02};

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
    // Set input Pin Mode
    for (int i = 0; i < MaxInputPin; i++)
    {
        pinMode(InputSwitchList[i], INPUT);
        pinMode(RelayPinList[i], OUTPUT);
    }
}

void WeMo_NodeMCU::Loop()
{
}