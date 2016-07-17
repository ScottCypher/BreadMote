#include <ESP8266WiFi.h>
#include <BreadMote.h>
//192.168.4.1
const char *ssid = "BreadMote";
const char *password = "88888888";

WiFiServer server(80);
WiFiClient client;

//-----------------------------------------------------------------------
//--------------------- Boilerplate I/O methods -------------------------

//Read data from your Bluetooth / Wi-Fi radio
char BreadMote::readByte() {
  return (char) client.read();
}

//Check to see if a byte is available to read from your Bluetooth / Wi-Fi radio
int BreadMote::getAvailableBytes() {
  return client.available();
}

//Writes to your Bluetooth / Wi-Fi radio
void BreadMote::write(char buf[], int len) {
   const uint8_t* bufCast = reinterpret_cast<const uint8_t*>(buf);
   size_t lenCast = (size_t)len;
   client.write(bufCast, lenCast);
}


//-----------------------------------------------------------------------
//------ Customize interface and how app interaction are handled --------

void BreadMote::create() {

}

//-----------------------------------------------------------------------
//--------------------------- esp8266 methods ---------------------------

BreadMote breadMote;

void setup() {
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  
  server.begin();
}

void loop() {
  if (client.connected()) {
        //read data from the connected client
        breadMote.read();
    } else {
        //try to connect to a new client
        client = server.available();
    }
}
