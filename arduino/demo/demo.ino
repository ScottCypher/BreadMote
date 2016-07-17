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
//--------------------------- Arduino methods ---------------------------

BreadMote breadMote;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop() {
  breadMote.read();//continuously called to read and write information to the remote
}
