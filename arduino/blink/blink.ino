#include <BreadMote.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(4, 2); // RX, TX

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

void onClick() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);
}

void BreadMote::create() {
  addButton("Blink", onClick);
}

//-----------------------------------------------------------------------
//--------------------------- Arduino methods ---------------------------

BreadMote breadMote;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  breadMote.read();//continuously called to read and write information to the remote
}
