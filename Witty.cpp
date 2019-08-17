#include "Witty.h"

const int Witty::BUTTON_PIN = 4; // Define pin the button is connected to
const int Witty::LDR_PIN = A0;   // Define the analog pin the LDR is connected to
const int Witty::RedLed = D8;
const int Witty::GreenLed = D6;
const int Witty::BlueLed = D7;
int Witty::btn_Status = HIGH;
bool Witty::wifiConnected = false;

void Witty::InitWitty()
{

  //Wity Init
  pinMode(RedLed, OUTPUT);
  pinMode(GreenLed, OUTPUT);
  pinMode(BlueLed, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Initialize button pin with built-in pullup.
  digitalWrite(BlueLed, HIGH);
  Serial.println("Witty Init  done");
  delay(2000);
  digitalWrite(BlueLed, LOW);
  int c = 3;
  do
  {
    //int c=3;
    wifiConnected = connectWifi();
    if (wifiConnected)
      c = 0;
    else
      c = c - 1;

  } while (c > 0);

} // end of Setup

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

bool Witty::connectWifi()
{

  boolean state = true;
  int i = 0;
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting ...");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    analogWrite(BlueLed, random(0, 1023));
    if (i > 10)
    {
      state = false;
      break;
    }
    i++;
  }
  digitalWrite(BlueLed, LOW);
  if (state)
  {
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    digitalWrite(GreenLed, HIGH);
  }
  else
  {
    Serial.println("");
    Serial.println("Connection failed.");
    digitalWrite(RedLed, HIGH);
  }

  return state;
}

int Witty::isButtonPressed()
{
  //Call this function in loop with better use case

  return digitalRead(BUTTON_PIN);
}
bool Witty::HandelButton(CallbackFunction cb)
{
  //Calling CallbackFunction
  return cb();
}
bool Witty::ResetDevice()
{
  //TODO: add code to reset device.
  ESP.restart();
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
