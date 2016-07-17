#include <Arduino.h>
#include <BreadMote.h>

//-----------------------------------------------------------------------
//--------------------- Boilerplate I/O methods -------------------------

//Read data from your Bluetooth / Wi-Fi radio
char BreadMote::readByte() {

}

//Check to see if a byte is available to read from your Bluetooth / Wi-Fi radio
int BreadMote::getAvailableBytes() {

}

//Writes to your Bluetooth / Wi-Fi radio
void BreadMote::write(char buf[], int len) {

}

//-----------------------------------------------------------------------
//------ Customize interface and how app interaction are handled --------

void BreadMote::create() {

}

//-----------------------------------------------------------------------
//--------------------------- Arduino methods ---------------------------

BreadMote breadMote;

void setup() {

}

void loop() {
  breadMote.read();//continuously called to read and write information to the remote
}
