//This is config file for project , Here you can decide what product you want to make
// Device Type can be marked here 
//Config Here

#define WEMO_SWITCH ;
#define WEMOS ; //Wemos switch 
#define WeatherStation ;// Weather station 
#define SENSOR ; // Sensor 
#define GATEWAY ; // Gateway server
#define DEVICETYPE WEMOS // What type of device it will be 

#define WEBSERVER ;   // WebServer.. Give basic web interface to on Off
//#define WITTY ;       //Witty Cloud board  very just 3 pin for input or output . good for sensor module
//#define ESP32 ;       // ESP32 Boad dev kit rev1
#define NODEMCU ;     // Esp8266  or nodemcu board
#define Alexa ;       // WeMo Switch support with Alexa ( Will Be working for google and other)
#define RetroSwitch ; // To be Used with old/ exisiting wiring
#define MQTT ;        // Enbaling MQTT
#define WEBAPI ;      // Enabling WebApi to control Switches and board .. In version 2.0
#define ASYNC_TCP_SSL_ENABLED  1 //  SSL MQT
// Config ends here