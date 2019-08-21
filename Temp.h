#ifndef TEMP_H
#define TEMP_H

 #include <Adafruit_Sensor.h>
#include <dht.h>
#include <Arduino.h>
#include <Hash.h>
//#include <DHT.h>

class Tempature
{

private:
    static int DHTPin;
    static int DHTType;

    static DHT dht;//(5, 11);

public:
    static float Temp_C;
    static float Humidity;

    Tempature(int pin, int senType);
    float readDHTHumidity();

    float readDHTTemperature();
};

#endif