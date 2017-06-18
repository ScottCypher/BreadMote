###Developer links

* [Installation & Documentation](#installation--documentation)
* [Templates](#templates)
* [Examples](#examples)

###BreadMote

Giving your invention an app is now as easy as buttering bread. Simply import the BreadMote library into your hardware, add code to customize the app, and decide how to handle user input. That's it! When BreadMote connects to your hardware you will see your app.

There are plenty of examples to get you started. BreadMote currently supports Wi-Fi and Bluetooth connections.

###Why BreadMote?

*Simple* - you only code on your hardware. There's no setup needed on the app itself!

*Customizable* - switches, time pickers, sliders, labels, and more! All displayed with names you pick and arranged how you specify

*Dynamic* - update, disable, add, or remove any component at any time

*Troubleshooting Aid* - display error messages directly on your phone rather than guess whats going on in your hardware

###Installation & Documentation

You'll need the app. It's currently only on [Android](https://play.google.com/apps/testing/com.cypher.breadmote)

**Arduino** - follow [this guide](https://www.arduino.cc/en/Guide/Libraries) to install the [C++ library](https://github.com/ScottCypher/BreadMote/tree/master/libraries/c%2B%2B/)

**ESP8266** - Using the Arduino IDE, follow [this guide](https://www.arduino.cc/en/Guide/Libraries) to install the [C++ library](https://github.com/ScottCypher/BreadMote/tree/master/libraries/c%2B%2B/)

Documentation for the C++ library can be found [here](http://scottcypher.github.io/BreadMote/libraries/c++/class_bread_mote.html)


###Sample code
Blink a light, all from your phone!

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

And here's what the corresponding remote would look like:

![alt text](http://scottcypher.github.io/BreadMote/screenshot.png "Blink BreadMote screenshot")


###Templates

* [Arduino](https://github.com/ScottCypher/BreadMote/blob/master/arduino/template/template.ino)
* [ESP8266](https://github.com/ScottCypher/BreadMote/blob/master/esp8266/template/template.ino)

###Examples

**Blink** - Blink an LED on your hardware using the app

* [Arduino](https://github.com/ScottCypher/BreadMote/blob/master/arduino/blink/blink.ino)
* [ESP8266](https://github.com/ScottCypher/BreadMote/blob/master/esp8266/blink/blink.ino)

**Print** - Print all user interaction to your hardware's serial monitor

* [Arduino](https://github.com/ScottCypher/BreadMote/blob/master/arduino/demo/demo.ino)
* [ESP8266](https://github.com/ScottCypher/BreadMote/blob/master/esp8266/demo/demo.ino)

**Advanced** - Log errors on Breadmote and disable parts of the UI dynamically

* [Arduino](https://github.com/ScottCypher/BreadMote/blob/master/arduino/advanced/advanced.ino)
* [ESP8266](https://github.com/ScottCypher/BreadMote/blob/master/esp8266/advanced/advanced.ino)

###The future

There are currently plans to add:

* more hardware support
* an app for iOS
* more connection protocols (e.g. Wi-Fi Direct and Bluetooth Low Energy)
* more features (e.g. streaming audio and video from your hardware)

If you are interested in contributing, contact me at scottcypher14@gmail.com

###Communication protocol

If you want to port BreadMote to another hardware, information about the protocol can be found [here](http://scottcypher.github.io/BreadMote/protocol.md). Be sure to check out existing the existing libraries for example implementations.

###Awesome projects

If your project uses BreadMote, I'd love to showcase it here! Contact me at scottcypher14@gmail.com
