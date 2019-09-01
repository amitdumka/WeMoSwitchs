/*
   Four Channel Relayed Based on wemos switches
   By: Amit Kumar (2019)
   Version 1.0
*/

#include "Config.h"

static const double DeviceId = 5458979879;
#ifdef WeatherStation

#include "WeatherStation.h"

#endif

#ifdef WEMO_SWITCH
#include "WeMo_Main.h"
WeMo_Main weMoMain;
#endif

void setup()
{
  Serial.begin(115200);
CallWiFiManager(false); //Call to connect to Wifi NetWork;
#ifdef WeatherStation
Serial.println("Weather Station is activated");
  WeatherStationSetup();
#endif
#ifdef WEMO_SWITCH
Serial.prinln("Wemo Switch is activated");
  weMoMain.CallInSetUp();
#endif

} // end of Setup

void loop()
{
  

#ifdef WEMO_SWITCH
  weMoMain.CallInLoop();
#endif
#ifdef WeatherStation
  WeatherStationLoop();
#endif
}
