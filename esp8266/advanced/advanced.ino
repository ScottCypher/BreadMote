#include <ESP8266WiFi.h>
#include <BreadMote.h>
//192.168.4.1
const char *ssid = "BreadMote";
const char *password = "88888888";

WiFiServer server(80);
WiFiClient client;
BreadMote breadMote;

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

void onButton() {
  breadMote.logError("Example", "Of a user generated error");
}

void onSwitch(bool b) {
  breadMote.setEnabled("Trigger log", b);
}

void onCheckbox(bool b) {
  breadMote.update(">>%s<<", b ? "checkbox on" : "checkbox off");
}

void BreadMote::create() {
  addButton("Trigger log", onButton);
  addSwitch("Toggle log button", onSwitch, true);
  addCheckBox("Update text", onCheckbox, false);
  addLabel(">>%s<<", "This will be updated");
}

//-----------------------------------------------------------------------
//--------------------------- esp8266 methods ---------------------------


void setup() {
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  
  server.begin();

  pinMode(BUILTIN_LED, OUTPUT);
  Serial.begin(115200);
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
