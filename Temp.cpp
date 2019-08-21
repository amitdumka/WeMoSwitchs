#include "Temp.h"

//Default:
int Tempature::DHTPin = 5;
int Tempature::DHTType = DHT11;

Tempature::Tempature(int pin, int senType)
{
    DHTPin = pin;
    DHTType = senType;
    dht= DHT(DHTPin, DHTType);
}

float Tempature::readDHTHumidity()
{
    float h = dht.readHumidity();
    if (isnan(h))
    {
        Serial.println("Failed to read from DHT sensor!");
        return -999.99;
    }
    else
    {
        Serial.println(h);
        return h;
    }
}

float Tempature::readDHTTemperature()
{
    float t = dht.readTemperature();
    if (isnan(t))
    {
        Serial.println("Failed to read from DHT sensor!");
        return -999.99;
    }
    else
    {
        Serial.println(t);
        return t;
    }
}