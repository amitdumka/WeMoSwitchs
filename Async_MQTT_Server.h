#ifndef ASYNC_MQTT_SERVER_H
#define ASYNC_MQTT_SERVER_H

#include "config.h"
#include <AsyncMqttClient.h>
#include <Ticker.h>

#ifdef NODEMCU
#include <ESP8266WiFi.h>
#endif

#ifdef ESP32
#include <WiFi.h>
extern "C"
{
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
}
#endif

#if ASYNC_TCP_SSL_ENABLED
#define MQTT_SECURE true
#define MQTT_SERVER_FINGERPRINT                                                                                                \
    {                                                                                                                          \
        0x7e, 0x36, 0x22, 0x01, 0xf9, 0x7e, 0x99, 0x2f, 0xc5, 0xdb, 0x3d, 0xbe, 0xac, 0x48, 0x67, 0x5b, 0x5d, 0x47, 0x94, 0xd2 \
    }
#define MQTT_PORT 8883
#else
#define MQTT_PORT 1883
#endif


#define MQTT_HOST IPAddress(192, 168, 1, 10)
//#define MQTT_PORT 1883

class Async_MQTT
{
private:
    static AsyncMqttClient mqttClient;
    static WiFiEventHandler wifiConnectHandler;
    static WiFiEventHandler wifiDisconnectHandler;

#ifdef NODEMCU
    static Ticker mqttReconnectTimer;
    static Ticker wifiReconnectTimer;

#endif

#ifdef ESP32
    static TimerHandle_t mqttReconnectTimer;
    static TimerHandle_t wifiReconnectTimer;
#endif

    static void onWifiConnect(const WiFiEventStationModeGotIP &event);
    static void onWifiDisconnect(const WiFiEventStationModeDisconnected &event);

    static void connectToMqtt();
    static void connectToWifi();

    static void onMqttPublish(uint16_t packetId);
    static void onMqttConnect(bool sessionPresent);
    static void onMqttDisconnect(AsyncMqttClientDisconnectReason reason);
    static void onMqttSubscribe(uint16_t packetId, uint8_t qos);
    static void onMqttUnsubscribe(uint16_t packetId);
    static void onMqttMessage(char *topic, char *payload, AsyncMqttClientMessageProperties properties, size_t len, size_t index, size_t total);

#ifdef ESP32
    static void WiFiEvent(WiFiEvent_t event);
#endif
public:
    void l() {}
    void mqtt_loop();
    void mqtt_setup();
};

#endif
