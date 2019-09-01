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
float Tempature::ReadDHTSenor(){
    Humidity = dht.readHumidity();
    Temp_C = dht.readTemperature();
    if (isnan(Humidity) ||isnan(Temp_C))
    {
        Serial.println("Failed to read from DHT sensor!");
        return -999.99;
    }
    else
    {
        HeatIndex = dht.computeHeatIndex(Temp_C, Humidity, false); // Compute heat index in Celsius
        Serial.print("Humidity: ");
        Serial.println(Humidity);
        Serial.print("Temp: ");
        Serial.println(Temp_C);
        Serial.print("Heat Index: ");
        Serial.println(HeatIndex);
        
        return Temp_C;
    }
    

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
    HeatIndex = dht.computeHeatIndex(Temp_C, Humidity, false); // Compute heat index in Celsius
    return HeatIndex;
    
}