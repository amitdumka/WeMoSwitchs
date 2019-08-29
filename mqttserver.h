#ifndef MQTT_SERVER_H
#define MQTT_SERVER_H

#include <functional>
#include <ArduinoJson.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Bounce2.h>
#include <DHT.h>
#include <string.h>

// MQTT
#define CONFIG_MQTT_HOST "{MQTT-SERVER}"
#define CONFIG_MQTT_PORT 1883 // Usually 1883
#define CONFIG_MQTT_USER "{MQTT-USERNAME}"
#define CONFIG_MQTT_PASS "{MQTT-PASSWORD}"
#define CONFIG_MQTT_CLIENT_ID "ESP_LED" // Must be unique on the MQTT network

#define DHTPIN 2      // what digital pin we're connected to
#define DHTTYPE DHT22 // DHT 22  (AM2302), AM2321

typedef void (*MQTT_Handler)(char *topic, byte *payload, unsigned int length);

class MQTT_Client
{
private:
    static String MQTT_Server;
    static int MQTT_Port;
    static String MQTT_UserName;
    static String MQTT_Password;
    static String MQTT_Client_ID;

    WiFiClient espClient;
    PubSubClient client;

    // Basic Topic
    //topic to subscribe to request for software version (Generic Device, MAC Addr, Filename.ino)
    const char *swVerTopic = "/MQTT_Client_ID/SwVerCommand";
    char swVerThisDeviceTopic[50];

    //topic to publish request for software version
    const char *swVerConfirmTopic = "/MQTT_Client_ID/SwVerConfirm";

    String clientName;
    const char *THIS_GENERIC_DEVICE = "esp8266"; //TODO: This need to be set Based on Board Select. Need to be implemented
    String swVersion;

    String macToStr(const uint8_t *mac);

public:

    MQTT_Client();
    MQTT_Client(String host);
    MQTT_Client(String host, int port);
    MQTT_Client(String host, int port, String username, String password);

    void SetUp(MQTT_Handler handler);
    void Loop();
    void Connect();
    bool BasicHandler(String topic); //TODO: Must be called on callback Handler. Other wise it can fail.

    void Publish(const char * topic, const char * payload);
    void Subscribe(const char * topic);

    //Array List Subricptions
    void Subscribe(String topicList[]); // Any String array need to pass and formate the subscribtion part.
    

};

#endif

//CPP Part Move to Cpp file

void MQTT_Client::SetUp(MQTT_Handler handler)
{
    client = PubSubClient(espClient);
    client.setServer(CONFIG_MQTT_HOST, CONFIG_MQTT_PORT);

    client.setCallback(handler);
    // Generate client name based on MAC address and last 8 bits of microsecond counter

    clientName = THIS_GENERIC_DEVICE;
    clientName += '-';
    uint8_t mac[6];
    WiFi.macAddress(mac);
    clientName += macToStr(mac);

    sprintf(swVerThisDeviceTopic, "/MQTT_Client_ID/%s/SwVerCommand", macToStr(mac).c_str());

    swVersion = THIS_GENERIC_DEVICE;
    swVersion += ',';
    swVersion += macToStr(mac);

    Serial.print("Client Name : ");
    Serial.println(clientName);
    Serial.print("SW Version : ");
    Serial.println(swVersion);

    Connect();

    //wait a bit before starting the main loop
    delay(2000);
}

//client.publish(buttonTopic, "Pressed");

void MQTT_Client::Loop()
{

    //reconnect if connection is lost
    if (!client.connected() && WiFi.status() == 3)
    {
        Connect();
    }

    //maintain MQTT connection
    client.loop();

    //MUST delay to allow ESP8266 WIFI functions to run
    delay(10);

    //monitor the button
    //checkButton();
    //checkTemperatureAndHumidity();
}

bool MQTT_Client::BasicHandler(String topicStr)
{

    if ((String)swVerTopic == topicStr)
    {
        client.publish(swVerConfirmTopic, swVersion.c_str());
        return;
    }

    if ((String)swVerThisDeviceTopic == topicStr)
    {
        client.publish(swVerConfirmTopic, swVersion.c_str());
        return;
    }
}

//generate unique name from MAC addr
String MQTT_Client::macToStr(const uint8_t *mac)
{ //TODO: Need to move to Lib part so can used any where

    String result;

    for (int i = 0; i < 6; ++i)
    {
        if ((mac[i] & 0xF0) == 0)
            result += String(0, HEX); // stop suppression of leading zero
        result += String(mac[i], HEX);

        if (i < 5)
        {
            result += ':';
        }
    }

    return result;
}
void MQTT_Client::Subscribe(const char * topic) { client.subscribe(topic); }
void MQTT_Client::Publish(const char * topic, const char * payload)
{
    client.publish(topic, payload);
}

//TODO: Make it sure it is non Blocking and Aysnc Mode
void MQTT_Client::Connect()
{

    //make sure we are connected to WIFI before attemping to reconnect to MQTT
    if (WiFi.status() == WL_CONNECTED)
    {
        // Loop until we're reconnected to the MQTT server
        while (!client.connected())
        {
            Serial.print("Attempting MQTT connection...");
            //if connected, subscribe to the topic(s) we want to be notified about
            if (client.connect((char *)clientName.c_str()))
            {
                Serial.print("\tMTQQ Connected");
                client.publish(swVerConfirmTopic, swVersion.c_str());
                client.subscribe(swVerThisDeviceTopic);
                client.subscribe(swVerTopic);
            }

            //otherwise print failed for debugging
            else
            {
                Serial.println("\tFailed.");
                abort();
            }
        }
    }
}