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
    Humidity = dht.readHumidity();
    if (isnan(Humidity))
    {
        Serial.println("Failed to read from DHT sensor!");
        return -999.99;
    }
    else
    {
        Serial.println(Humidity);
        return Humidity;
    }
}

float Tempature::readDHTTemperature()
{
    Temp_C = dht.readTemperature();
    
    if (isnan(Temp_C))
    {
        Serial.println("Failed to read from DHT sensor!");
        return -999.99;
    }
    else
    {
        Serial.println(Temp_C);
        return Temp_C;
    }
}

float Tempature::readDHTHeatIndex(){
    readDHTHumidity();readDHTTemperature();
    HeadIndex = dht.computeHeatIndex(Temp_C, Humidity, false); // Compute heat index in Celsius
    return HeadIndex;
    
}