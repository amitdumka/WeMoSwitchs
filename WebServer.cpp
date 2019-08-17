#include "WebServer.h"

const int WebServer::output1 = 1;
const int WebServer::output2 = 2;
const int WebServer::output3 = 3;
const int WebServer::output4 = 4;
const long WebServer::timeoutTime = 2000;


bool WebServer::StartWebServer()
{
  server->begin();
  Serial.print("Open http://");
  Serial.print(WiFi.localIP());
  Serial.println("/ in your browser to see it working");
  return true;
}


WebServer::WebServer()
{
  server = new WiFiServer(80);
}
WebServer::WebServer(int port)
{

  server = new WiFiServer(port);
}

//WiFiServer based

void WebServer::EndDoc(WiFiClient client)
{
  client.println("</body></html>");
  // The HTTP response ends with another blank line
  client.println();
}
void WebServer::RootDoc(WiFiClient client)
{
  if (!client)
    client = server->available(); // Listen for incoming clients

  if (client)
  {                                // If a new client connects,
    Serial.println("New Client."); // print a message out in the serial port
    String currentLine = "";       // make a String to hold incoming data from the client
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime)
    { // loop while the client's connected
      currentTime = millis();
      if (client.available())
      {                         // if there's bytes to read from the client,
        char c = client.read(); // read a byte, then
        Serial.write(c);        // print it out the serial monitor
        header += c;
        if (c == '\n')
        { // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0)
          {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // turns the Switchs on and off
            if (header.indexOf("GET /1/on") >= 0)
            {
              Serial.println("Switch 1 on");
              output1State = "on";
              digitalWrite(output1, HIGH);
            }
            else if (header.indexOf("GET /1/off") >= 0)
            {
              Serial.println("Switch 1 off");
              output1State = "off";
              digitalWrite(output1, LOW);
            }
            else if (header.indexOf("GET /2/on") >= 0)
            {
              Serial.println("Switch 2 on");
              output2State = "on";
              digitalWrite(output2, HIGH);
            }
            else if (header.indexOf("GET /2/off") >= 0)
            {
              Serial.println("Switch 2 off");
              output2State = "off";
              digitalWrite(output2, LOW);
            }

            else if (header.indexOf("GET /3/on") >= 0)
            {
              Serial.println("Switch 3 on");
              output3State = "on";
              digitalWrite(output3, HIGH);
            }
            else if (header.indexOf("GET /3/off") >= 0)
            {
              Serial.println("Switch 3 off");
              output3State = "off";
              digitalWrite(output3, LOW);
            }

            else if (header.indexOf("GET /4/on") >= 0)
            {
              Serial.println("Switch 4 on");
              output4State = "on";
              digitalWrite(output4, HIGH);
            }
            else if (header.indexOf("GET /4/off") >= 0)
            {
              Serial.println("Switch 4 off");
              output4State = "off";
              digitalWrite(output4, LOW);
            }

            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>table {display: table; border-spacing: 15px; text-align: center; border: 2px solid green; background-color: #f1f1c1; align:center; } </style>");
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;} h1 {  color: rgb(0, 221, 152); font-family: verdana; font-size: 300%;}</style></head>");

            // Web Page Heading
            client.println("<body><h1>Amit IOT Switch</h1>");
            client.println("<table align='center'><tr><td>");

            // Display current state, and ON/OFF buttons for Switch 1
            client.println("Switch 1 - State " + output1State + "");
            // If the output1State is off, it displays the ON button
            if (output1State == "off")
            {
              client.println("<a href=\"/1/on\"><button class=\"button\">ON</button></a>");
            }
            else
            {
              client.println("<a href=\"/1/off\"><button class=\"button button2\">OFF</button></a>");
            }

            client.println("</td><td>");

            // Display current state, and ON/OFF buttons for Switch 2

            client.println("Switch 2 - State " + output2State + "");
            // If the output2State is off, it displays the ON button
            if (output2State == "off")
            {
              client.println("<a href=\"/2/on\"><button class=\"button\">ON</button></a>");
            }
            else
            {
              client.println("<a href=\"/2/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("</td></tr><tr><td>");

            // Display current state, and ON/OFF buttons for Switch 3
            client.println("Switch 3 - State " + output3State + "");
            // If the output3State is off, it displays the ON button
            if (output3State == "off")
            {
              client.println("<a href=\"/3/on\"><button class=\"button\">ON</button></a>");
            }
            else
            {
              client.println("<a href=\"/3/off\"><button class=\"button button2\">OFF</button></a>");
            }
            client.println("</td><td>");
            // Display current state, and ON/OFF buttons for Switch 4

            client.println("Switch 4 - State " + output4State + "");
            // If the output4State is off, it displays the ON button
            if (output4State == "off")
            {
              client.println("<a href=\"/4/on\"><button class=\"button\">ON</button></a>");
            }
            else
            {
              client.println("<a href=\"/4/off\"><button class=\"button button2\">OFF</button></a>");
            }
            client.println("</td></tr></table>");

            client.println("</body></html>");

            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          }
          else
          { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        }
        else if (c != '\r')
        {                   // if you got anything else but a carriage return character,
          currentLine += c; // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
} //end of rootdoc

void WebServer::AddButton(String switchName, String outputState, int index, WiFiClient client)
{
  // Display current state, and ON/OFF buttons for Switch

  client.print(switchName + " - State " + outputState + "");
  // If the outputState is off, it displays the ON button
  Serial.println("AddButton: "+outputState);

  if (outputState == "off")
  {
    client.print("<a href=\"/");
    client.print(index);
    client.println("/on\"><button class=\"button\">ON</button></a>");
  }
  else
  {
    client.print("<a href=\"/");
    client.print(index);
    client.println("/off\"><button class=\"button button2\">OFF</button></a>");
  }
}

void WebServer::OperateRelay(int switchIndex, int onOff)
{
  switch (switchIndex)
  {
  case 1:
    
    output1State = (onOff == HIGH ? "on" : "off");
    Serial.println("Switch 1 on: "+output1State);
    digitalWrite(output1, onOff);
    break;
  case 2:
    output2State = (onOff == HIGH ? "on" : "off");
    Serial.println("Switch 2 on: "+output2State);
    digitalWrite(output2, onOff);
    break;
  case 3:
    output3State = (onOff == HIGH ? "on" : "off");
    Serial.println("Switch 3 on: "+output3State);
    digitalWrite(output3, onOff);
    break;
  case 4:
    output4State = (onOff == HIGH ? "on" : "off");
    Serial.println("Switch 4 on: "+output4State);
    digitalWrite(output4, onOff);
    break;
  default:
    break;
  }
}

void WebServer::ButtonSelect()
{

  // turns the Switchs on and off
  if (header.indexOf("GET /1/on") >= 0)
  {
    OperateRelay(1, HIGH);
  }
  else if (header.indexOf("GET /1/off") >= 0)
  {
    OperateRelay(1, LOW);
  }
  else if (header.indexOf("GET /2/on") >= 0)
  {
    OperateRelay(2, HIGH);
  }
  else if (header.indexOf("GET /2/off") >= 0)
  {
    OperateRelay(2, LOW);
  }
  else if (header.indexOf("GET /3/on") >= 0)
  {
    OperateRelay(3, HIGH);
  }
  else if (header.indexOf("GET /3/off") >= 0)
  {
    OperateRelay(3, LOW);
  }
  else if (header.indexOf("GET /4/on") >= 0)
  {
    OperateRelay(4, HIGH);
  }
  else if (header.indexOf("GET /4/off") >= 0)
  {
    OperateRelay(4, LOW);
  }
}

void WebServer::IndexPage()
{
  WiFiClient client = server->available(); // Listen for incoming clients
  if (client)
  {                                // If a new client connects,
    Serial.println("New Client."); // print a message out in the serial port
    String currentLine = "";       // make a String to hold incoming data from the client
    currentTime = millis();
    previousTime = currentTime;

    //While
    while (client.connected() && currentTime - previousTime <= timeoutTime)
    { // loop while the client's connected
      currentTime = millis();
      if (client.available())
      {
        char c = client.read(); // read a byte, then
      //  Serial.write(c);        // print it out the serial monitor
        header += c;

        if (c == '\n')
        {
          if (currentLine.length() == 0)
          {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            ButtonSelect(); // Check Button Status and OperateRelay
            WebBody(client);
            client.println("<table align='center'><tr><td>");
            AddButton("Switch One", output1State, 1, client);
            client.println("</td><td>");
            AddButton("Switch Two", output2State, 2, client);
            client.println("</td></tr><tr><td>");
            AddButton("Switch Three", output3State, 3, client);
            client.println("</td><td>");
            AddButton("Switch Four", output4State, 4, client);
            client.println("</td></tr></table>");

            EndDoc(client);
          }
          else
          { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        }
        else if (c != '\r')
        {                   // if you got anything else but a carriage return character,
          currentLine += c; // add it to the end of the currentLine
        }
      }
    }

    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    //Serial.println("");
  }
}

void WebServer::WebBody(WiFiClient client)
{
  // Display the HTML web page
  client.println("<!DOCTYPE html><html>");
  client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  client.println("<link rel=\"icon\" href=\"data:,\">");
  // CSS to style the on/off buttons
  // Feel free to change the background-color and font-size attributes to fit your preferences
  client.println("<style>table {display: table; border-spacing: 15px; text-align: center; border: 2px solid green; background-color: #f1f1c1; align:center; } </style>");
  client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
  client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
  client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
  client.println(".button2 {background-color: #77878A;} h1 {  color: rgb(0, 221, 152); font-family: verdana; font-size: 300%;}</style></head>");

  // Web Page Heading
  client.println("<body><h1>Amit IOT Switch</h1>");

  client.println("<table align='center'><tr><td>");
}
