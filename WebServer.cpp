#include "WebServer.h"

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
  client.println();
}

void WebServer::AddButton(String switchName, bool outputState, int index, WiFiClient client)
{
  // Display current state, and ON/OFF buttons for Switch
  client.print(switchName + " - State "  );
  client.print(outputState?"on":"off"  );
  if (!outputState )
  {
    client.print("<br><a href=\"/");
    client.print(index);
    client.println("/on\"><button class=\"button\">ON</button></a>");
  }
  else
  {
    client.print("<br><a href=\"/");
    client.print(index);
    client.println("/off\"><button class=\"button button2\">OFF</button></a>");
  }
}


void WebServer::ButtonSelect()
{
  if (header.indexOf("GET /1/on") >= 0)
  {
    WeMo::OperateRelay(0, HIGH);
  }
  else if (header.indexOf("GET /1/off") >= 0)
  {
    WeMo::OperateRelay(0, LOW);
  }
  else if (header.indexOf("GET /2/on") >= 0)
  {
    WeMo::OperateRelay(1, HIGH);
  }
  else if (header.indexOf("GET /2/off") >= 0)
  {
    WeMo::OperateRelay(1, LOW);
  }
  else if (header.indexOf("GET /3/on") >= 0)
  {
    WeMo::OperateRelay(2, HIGH);
  }
  else if (header.indexOf("GET /3/off") >= 0)
  {
    WeMo::OperateRelay(2, LOW);
  }
  else if (header.indexOf("GET /4/on") >= 0)
  {
    WeMo::OperateRelay(3, HIGH);
  }
  else if (header.indexOf("GET /4/off") >= 0)
  {
    WeMo::OperateRelay(3, LOW);
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
            AddButton(WeMo::RelayNames[0], WeMo::isRelayOn[0], 1, client);
            client.println("</td><td>");
            AddButton(WeMo::RelayNames[1], WeMo::isRelayOn[1], 2, client);
            client.println("</td></tr><tr><td>");
            AddButton(WeMo::RelayNames[2], WeMo::isRelayOn[2], 3, client);
            client.println("</td><td>");
            AddButton(WeMo::RelayNames[3], WeMo::isRelayOn[3], 4, client);
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
