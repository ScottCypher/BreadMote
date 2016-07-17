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

void onButton() {
  Serial.println("Button pressed");
}

void onSwitch(bool b) {
  Serial.print("Switch pressed: "); Serial.println(b);
}

void onCheckbox(bool b) {
  Serial.print("Checkbox pressed: "); Serial.println(b);
}

void onSlider(int i) {
  Serial.print("Slider change: "); Serial.println(i);
}

void onRadioGroup(int i) {
  Serial.print("Radiogroup item selected: "); Serial.println(i);
}

void onTextField(const char* text) {
  Serial.print("Text field: "); Serial.println(text);
}

void onTimePick(char hour, char minute) {
  Serial.print("Time picker: ");Serial.print((int)hour);Serial.print(":");Serial.println((int)minute);
}

void BreadMote::create() {
  addButton("Button", onButton);
  addSwitch("Switch", onSwitch, false);
  addCheckBox("Check box", onCheckbox, false);
  addSlider("Slider", onSlider, 0, 100, 50);
  const char* RADIO_OPTIONS[4] {"Option A", "Option B", "Option C", "Option D"};
  addRadioGroup("Radio group", onRadioGroup, RADIO_OPTIONS, 4, 0);
  addTextField("Text field", onTextField, "");
  addTimePicker("Time picker", onTimePick, 6, 30);
}

//-----------------------------------------------------------------------
//--------------------------- esp8266 methods ---------------------------

BreadMote breadMote;

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
