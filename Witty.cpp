#include "Witty.h"

int Witty::btn_Status = HIGH;

void Witty::InitWitty()
{
  //Wity Init
  pinMode(Witty::RedLed, OUTPUT);
  pinMode(GreenLed, OUTPUT);
  pinMode(BlueLed, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP); // Initialize button pin with built-in pullup.

  digitalWrite(BlueLed, HIGH);
  Serial.println("Witty Init  done");
  delay(2000);
  digitalWrite(BlueLed, LOW);
  LedStatus(WeMo::wifiConnected);

} // end of Init

void Witty::InitWitty(bool isConnected, bool isConfiged)
{
  //Wity Init
  pinMode(RedLed, OUTPUT);
  pinMode(GreenLed, OUTPUT);
  pinMode(BlueLed, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP); // Initialize button pin with built-in pullup.

  digitalWrite(BlueLed, HIGH);
  Serial.println("Witty Init  done");
  delay(2000);
  digitalWrite(BlueLed, LOW);
  if (isConfiged)
  {
    // Read all relay sate and set it  here
  }

  if (!isConnected)
  {
    isConnected = CallWiFiManager(false);
    WeMo::wifiConnected = isConnected;
  }
  LedStatus(isConnected);
}
void Witty::InitWitty(bool isConnected)
{
  //Wity Init
  pinMode(RedLed, OUTPUT);
  pinMode(GreenLed, OUTPUT);
  pinMode(BlueLed, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP); // Initialize button pin with built-in pullup.

  digitalWrite(BlueLed, HIGH);
  Serial.println("Witty Init  done");
  delay(2000);
  digitalWrite(BlueLed, LOW);

  if (!isConnected)
  {
    digitalWrite(BlueLed, HIGH); // option to make blinking till become green
    WeMo::wifiConnected = CallWiFiManager(false);
  }
  LedStatus(WeMo::wifiConnected);

} // end of Init(true)

void Witty::SetLedDigital(int r, int g, int b)
{
  digitalWrite(RedLed, r);
  digitalWrite(GreenLed, g);
  digitalWrite(BlueLed, b);
}

void Witty::SetLedAnalog(int r, int g, int b)
{
  analogWrite(RedLed, r);
  analogWrite(GreenLed, g);
  analogWrite(BlueLed, b);
}

bool Witty::setLedColor(int r, int g, int b)
{
  analogWrite(RedLed, random(r, 1023));
  analogWrite(GreenLed, random(g, 1023));
  analogWrite(BlueLed, random(b, 1023));
  return true;
}

int Witty::isButtonPressed()
{
  //Call this function in loop with better use case
  return digitalRead(BUTTON);
}
bool Witty::HandelButton(CallbackFunction cb)
{
  //Calling CallbackFunction
  return cb();
}
bool Witty::ResetDevice()
{
  ESP.reset();
  return true;
}

bool Witty::ReconnectWifi()
{
  if (!WeMo::wifiConnected)
  {
    ESP.reset();
  }
  return WeMo::wifiConnected;
}

void Witty::LedStatus(bool isConnected)
{
  digitalWrite(BlueLed, LOW);
  if (isConnected)
  {
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(WiFi.SSID());
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    digitalWrite(GreenLed, HIGH);
    digitalWrite(RedLed, LOW);
  }
  else
  {
    Serial.println("");
    Serial.println("Connection failed.");
    digitalWrite(RedLed, HIGH);
  }
}