#ifndef WEMO_ESP32_H
#define WEMO_ESP32_H

#include <Arduino.h>
#include <ESP8266WiFi.h>

class WeMo_ESP32
{
private:
    //input 34 35 36 39. [16,17,27,12]
    //output ,32 33 25 26 [21,22,04,02]
    // 16, 17, 21, 22, 27, 04 02
    // extra 12 13 14

    static const int MaxInputPin = 8;
    static const int MaxOutPutPin = 8;

    static int InputSwitchList[MaxInputPin]; //={34,35,35,39,27,16,17,12};
    static int RelayPinList[MaxOutPutPin];   //=   {32,33,25,26,21,22,04,02};

public:
    void Setup();
    void Loop();
};

#endif


//Move to CPP file
int WeMo_ESP32::InputSwitchList[MaxInputPin] = {34, 35, 35, 39, 27, 16, 17, 12};
int WeMo_ESP32::RelayPinList[MaxOutPutPin] = {32, 33, 25, 26, 21, 22, 04, 02};

void WeMo_ESP32::Setup()
{
    // Set input Pin Mode
    for (int i = 0; i < MaxInputPin; i++)
    {
        pinMode(InputSwitchList[i], INPUT);
        pinMode(RelayPinList[i], OUTPUT);
    }
}

void WeMo_ESP32::Loop()
{
}