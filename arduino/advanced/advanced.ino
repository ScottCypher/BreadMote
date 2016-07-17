#include <BreadMote.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(4, 2); // RX, TX
BreadMote breadMote;

//-----------------------------------------------------------------------
//--------------------- Boilerplate I/O methods -------------------------

//Read data from your Bluetooth / Wi-Fi radio
char BreadMote::readByte() {
  return mySerial.read();
}

//Check to see if a byte is available to read from your Bluetooth / Wi-Fi radio
int BreadMote::getAvailableBytes() {
  return mySerial.available();
}

//Writes to your Bluetooth / Wi-Fi radio
void BreadMote::write(char buf[], int len) {
  mySerial.write(buf, len);
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
//--------------------------- Arduino methods ---------------------------

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  breadMote.read();//continuously called to read and write information to the remote
}
