#include "Util.h"
bool CallWiFiManager(bool isNew)
{
    Serial.println("WiFi Manager is started...");
    WiFiManager wifiManager;
    if (isNew)
        wifiManager.resetSettings(); //reset settings - for testing
    wifiManager.setAPStaticIPConfig(WeMo::_IP, WeMo::_GW, WeMo::_SN);
    wifiManager.setTimeout(360);

    if (!wifiManager.autoConnect(WeMo::AP_Name.c_str()))
    {
        Serial.println("failed to connect and hit timeout");
        delay(3000);
        //reset and try again, or maybe put it to deep sleep
        ESP.reset();
        delay(5000);
    }
    //if you get here you have connected to the WiFi
    Serial.println("connected...yeey :)");
    WeMo::wifiConnected = true;
    Serial.println("local ip");
    Serial.println(WiFi.localIP());
    return WeMo::wifiConnected;
}
