#include "Witty.h"

int Witty::btn_Status = HIGH;
bool Witty::wifiConnected = false;

void Witty::InitWitty()
{
  //Wity Init
  pinMode(WeMo::RedLed, OUTPUT);
  pinMode(WeMo::GreenLed, OUTPUT);
  pinMode(WeMo::BlueLed, OUTPUT);
  pinMode(WeMo::BUTTON, INPUT_PULLUP); // Initialize button pin with built-in pullup.

  digitalWrite(WeMo::BlueLed, HIGH);
  Serial.println("Witty Init  done");
  delay(2000);
  digitalWrite(WeMo::BlueLed, LOW);

  int c = 3;
  do
  {
    //int c=3;
    if (wifiConnected)
    {
      LedStatus(wifiConnected);
      break;
    }

    wifiConnected = connectWifi();
    if (wifiConnected)
      c = 0;
    else
      c = c - 1;

  } while (c > 0);

} // end of Init

void Witty::InitWitty(bool isConnected, bool isConfiged)
{
  //Wity Init
  pinMode(WeMo::RedLed, OUTPUT);
  pinMode(WeMo::GreenLed, OUTPUT);
  pinMode(WeMo::BlueLed, OUTPUT);
  pinMode(WeMo::BUTTON, INPUT_PULLUP); // Initialize button pin with built-in pullup.

  digitalWrite(WeMo::BlueLed, HIGH);
  Serial.println("Witty Init  done");
  delay(2000);
  digitalWrite(WeMo::BlueLed, LOW);
  if (isConfiged)
  {
    // Read all relay sate and set it  here
  }

  if (!isConnected)
  {
    isConnected = CallWiFiManager(false);
    wifiConnected = isConnected;
  }
  LedStatus(isConnected);
}
void Witty::InitWitty(bool isConnected)
{
  //Wity Init
  pinMode(WeMo::RedLed, OUTPUT);
  pinMode(WeMo::GreenLed, OUTPUT);
  pinMode(WeMo::BlueLed, OUTPUT);
  pinMode(WeMo::BUTTON, INPUT_PULLUP); // Initialize button pin with built-in pullup.

  digitalWrite(WeMo::BlueLed, HIGH);
  Serial.println("Witty Init  done");
  delay(2000);
  digitalWrite(WeMo::BlueLed, LOW);

  if (!isConnected)
    {
      digitalWrite(WeMo::BlueLed, HIGH);// option to make blinking till become green
      wifiConnected = CallWiFiManager(false);
    }
    LedStatus(wifiConnected);

} // end of Init(true)

void Witty::SetLedDigital(int r, int g, int b)
{
  digitalWrite(WeMo::RedLed, r);
  digitalWrite(WeMo::GreenLed, g);
  digitalWrite(WeMo::BlueLed, b);
}

void Witty::SetLedAnalog(int r, int g, int b)
{
  analogWrite(WeMo::RedLed, r);
  analogWrite(WeMo::GreenLed, g);
  analogWrite(WeMo::BlueLed, b);
}

bool Witty::setLedColor(int r, int g, int b)
{
  analogWrite(WeMo::RedLed, random(r, 1023));
  analogWrite(WeMo::GreenLed, random(g, 1023));
  analogWrite(WeMo::BlueLed, random(b, 1023));
  return true;
}

bool Witty::connectWifi()
{
  boolean state = true;
  int i = 0;
  WiFi.mode(WeMo::WiFiMode);
  WiFi.begin(WeMo::SSID, WeMo::password);
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting ...");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    analogWrite(WeMo::BlueLed, random(0, 1023));
    if (i > 10)
    {
      state = false;
      break;
    }
    i++;
  }
  digitalWrite(WeMo::BlueLed, LOW);
  LedStatus(state);
  WeMo::wifiConnected=wifiConnected=state;
  return state;
}

int Witty::isButtonPressed()
{
  //Call this function in loop with better use case
  return digitalRead(WeMo::BUTTON);
}
bool Witty::HandelButton(CallbackFunction cb)
{
  //Calling CallbackFunction
  return cb();
}
bool Witty::ResetDevice()
{
  //TODO: add code to reset device.
  //ESP.restart();
  ESP.reset();
  return true;
}

bool Witty::ReconnectWifi()
{
  if (!wifiConnected)
  {
    wifiConnected = connectWifi();
  }
  return wifiConnected;
}

void Witty::LedStatus(bool isConnected)
{
  digitalWrite(WeMo::BlueLed, LOW);
  if (isConnected)
  {
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(WiFi.SSID());
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    digitalWrite(WeMo::GreenLed, HIGH);
    digitalWrite(WeMo::RedLed, LOW);
  }
  else
  {
    Serial.println("");
    Serial.println("Connection failed.");
    digitalWrite(WeMo::RedLed, HIGH);
  }
}