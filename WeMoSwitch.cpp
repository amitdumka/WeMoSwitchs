#include "WemoSwitch.h"


//<<constructor>>
WeMoSwitch::WeMoSwitch()
{

  
  
  if (!WeMo::wifiConnected)
    Serial.println("Wifi is not Connected");
}

//<<destructor>>
WeMoSwitch::~WeMoSwitch()
{
  Serial.println("Object of Wemos disposed...");
}

//Init Function , Must me called in Setup function
bool WeMoSwitch::initWemoSwitch()
{
  Serial.println("Initization of WemoSwitch box begin");
  if (WeMo::wifiConnected)
  {
    upnpBroadcastResponder.beginUdpMulticast();
    //*relaySwitch= new Switch[WeMo::NoOfRelay];  // TODO:solve this error
   
    // Define your switches here. Max 10
    for (int i = 0; i < WeMo::NoOfRelay; i++)
    {
      // Format: Alexa invocation name, local port no, on callback, off callback ,Index of Switch. 
      relaySwitch[i] = new Switch(WeMo::RelayNames[i], WeMo::RelayPort[i], SwitchOn, SwitchOff, i);
      upnpBroadcastResponder.addDevice(*relaySwitch[i]);
    }
    Serial.println("Adding switches upnp broadcast responder ");
    Serial.print(WeMo::NoOfRelay);
    Serial.println(" Switchs is added.");
  }
  else
  {
    Serial.println("Wifi In Not Connected  ");
    Serial.println(" No Switches added as no Wifi Connection present.");
    Serial.println("Kindly restart by pressing restart switch!");
    return false;
  }
  return true;
}

//WeMoSwitchLoop, Must be called in Loop() function.
void WeMoSwitch::wemoSwitchLoop()
{
  if (WeMo::wifiConnected)
  {
    upnpBroadcastResponder.serverLoop();
    for (int i = 0; i < WeMo::NoOfRelay; i++)
      relaySwitch[i]->serverLoop();
  }
  else
  {
    if (counter-- > 0)
      Serial.println("From Loop, Wifi is Connected or WifiConnected is not set.");
  }
}

//On/Off Callback function. 
//("Note: If every thing is static , then also no problem, most of thing will fixed a board and one board will not call more than one object. ");

bool WeMoSwitch::SwitchOff(int index)
{
  Serial.print(" Turning Off Switch");Serial.println(index + 1);
  WeMo::isRelayOn[index] = false;
  WeMo::OperateRelay(index, LOW);
  saveRelayConfiguration(WeMo::RelayNames[index], 0, WeMo::RelayNames[index] + index, false);
  return WeMo::isRelayOn[index];
}

bool WeMoSwitch::SwitchOn(int index)
{
  Serial.print(" Turning ON Switch");Serial.println(index + 1);
  WeMo::isRelayOn[index] = true;
  WeMo::OperateRelay(index, HIGH);
  saveRelayConfiguration(WeMo::RelayNames[index], 1, WeMo::RelayNames[index] + index, true);
  return WeMo::isRelayOn[index];
}




