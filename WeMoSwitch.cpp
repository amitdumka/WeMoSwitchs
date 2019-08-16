#include"WemoSwitch.h"

bool WeMoSwitch::isRelayOneOn = false;
bool WeMoSwitch::isRelayTwoOn = false;
bool WeMoSwitch::isRelayThreeOn = false;
bool WeMoSwitch::isRelayFourOn = false;



//<<constructor>>
WeMoSwitch::WeMoSwitch()
{
  //wittyb=board;

}

WeMoSwitch::WeMoSwitch(Witty b)
{
  wittyB = b;
  if (wittyB.wifiConnected == false) {
    Serial.println("Connecting Again..");
    wifiConnected = wittyB.wifiConnected = wittyB.connectWifi();
  }
  wifiConnected=wittyB.wifiConnected;
  if(!wifiConnected) Serial.println("WifiConnected is False");
}

WeMoSwitch::WeMoSwitch(Witty b, WebServer s)
{
  wittyB = b;
  webServer=s;
  if (wittyB.wifiConnected == false) {
    Serial.println("Connecting Again..");
    wifiConnected = wittyB.wifiConnected = wittyB.connectWifi();
  }
  wifiConnected=wittyB.wifiConnected;
  if(!wifiConnected) Serial.println("WifiConnected is False");
}
WeMoSwitch::WeMoSwitch(bool con){wifiConnected=con;/*//TODO: if wificonnected  return or chash or something to handel*/}
//<<destructor>>
WeMoSwitch::~WeMoSwitch()
{
  // wittyB=NULL;

  Serial.println("Object of Wemos disposed...");
}

//Init Function , Must me called in Setup function 
bool WeMoSwitch::initWemoSwitch()
{
  Serial.println("Initization of WemoSwitch box begin");
  
  // Initialise wifi connection
  if (wifiConnected == false)
    {
      Serial.println("Wifi In Not Connected, trying to connect again....");
      wifiConnected = wittyB.connectWifi();
    }

  if (wifiConnected) {
    upnpBroadcastResponder.beginUdpMulticast();
   
    // Define your switches here. Max 10
    // Format: Alexa invocation name, local port no, on callback, off callback
    relayOne = new Switch("Switch One", 81,  SwitchTwoOn, SwitchTwoOff);
    relayTwo = new Switch("Switch Two", 82, SwitchTwoOn, SwitchTwoOff);
    relayThree = new Switch("Switch Three", 83, SwitchThreeOn, SwitchThreeOff);
    relayFour = new Switch("Switch Four", 84, SwitchFourOn, SwitchFourOff);

    Serial.println("Adding switches upnp broadcast responder");
    //By Amit Kumar
    upnpBroadcastResponder.addDevice(*relayOne);
    upnpBroadcastResponder.addDevice(*relayTwo);
    upnpBroadcastResponder.addDevice(*relayThree);
    upnpBroadcastResponder.addDevice(*relayFour);
    Serial.println("Four Switchs is added.");

  }
  else{
    Serial.println(" No Switches added as no Wifi Connection present.");
    Serial.println("Kindly restart by pressing restart switch!");
    }
}

//WeMoSwitchLoop, Must be called in Loop() function. 
bool WeMoSwitch::wemoSwitchLoop() {
  
  if (wifiConnected) {
    upnpBroadcastResponder.serverLoop();
    
    relayOne->serverLoop();
    relayTwo->serverLoop();
    relayThree->serverLoop();
    relayFour->serverLoop();
  }else 
  {
    if(counter-->0)
    Serial.println("From Loop, Wifi is Connected or WifiConnected is not set.");
    
  }
  
}

void WeMoSwitch::WebLoop()
{
//  webServer.server->on("/", [&]() {
//    handleRoot();
//  });
// 
// webServer.server->on(":81/1", [&]() {
//    handleON();
//  });
// webServer.server->on(":81/0", [&]() {
//    handleOFF();
//  });
// 
  
}

//On/Off Callback function. ("Note: If every thing is static , then also no problem, most of thing will fixed a board and one board will not call more than one object. ");
bool WeMoSwitch::SwitchOneOn() {
  Serial.println("Switch 1 turn on ...");
  isRelayOneOn = true;
  return isRelayOneOn;
}

bool WeMoSwitch::SwitchOneOff() {
  Serial.println("Switch 1 turn off ...");
  isRelayOneOn = false;
  return isRelayOneOn;
}

bool WeMoSwitch::SwitchTwoOn() {
  Serial.println("Switch 2 turn on ...");
  isRelayTwoOn = true;
  return isRelayTwoOn;
}

bool WeMoSwitch::SwitchTwoOff() {
  Serial.println("Switch 2 turn off ...");
  isRelayTwoOn = false;
  return isRelayTwoOn;
}

bool WeMoSwitch::SwitchThreeOn() {
  Serial.println("Switch 3 turn on ...");
  isRelayThreeOn = true;
  return isRelayThreeOn;
}

bool WeMoSwitch::SwitchThreeOff() {
  Serial.println("Switch 3 turn off ...");
  isRelayThreeOn = false;
  return isRelayThreeOn;
}

bool WeMoSwitch::SwitchFourOn() {
  Serial.println("Switch 4 is turning on ...");
  isRelayFourOn = true;
  return isRelayFourOn;
}

bool WeMoSwitch::SwitchFourOff() {
  Serial.println("Switch 4 is turning ...");
  isRelayFourOn = false;
  return isRelayFourOn;
}

//Read RealyName to set by app.
char *WeMoSwitch::ReadRelayName(int index) {
  return NULL;
}

//Set RelayName ,set by App
bool WeMoSwitch::SetRelayName(int index, char *relayName) {
  return 0;
}

void WeMoSwitch::handleON()
{
  
}

void WeMoSwitch::handleOFF()
{
  
}
void WeMoSwitch::handleRoot(){
 // char *rootDoc=("<table><tr><tc> <a href="">SW1 On</a></tc><tc><a href=""> SW1 OFF</a></tc></tr> <tr><tc> SW2 On</tc><tc> SW2 OFF</tc></tr></table>");
  //webServer.Send(200, "text/html",rootDoc);
  
  }
