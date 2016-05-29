//
//  BreadMote.hpp
//  BreadMote
//
//  Created by Scott Cypher on 1/4/16.
//  Copyright © 2016 Scott Cypher. All rights reserved.
//

#ifndef BreadMote_h
#define BreadMote_h

#define TYPE_INT 0
#define TYPE_BOOL 1
#define TYPE_STRING 2

/**
 This class handles all communication between your hardware's radio and the BreadMote application, allowing you to create a custom app interface for your hardware. It also allows you to easily handle what each user interaction from the app does.
 
 Be sure to checkout the short and easy to follow examples found <a href="http://scottcypher.github.io#examples">here</a>
 */
/*
 Message format:
 [type][length][value]
 
 type - 1 byte
 length - 2 bytes (0 is valid and means no value), NOTE: except for the header, the device WRITES in its native int size, so 2 or 4. This is done to increase message size when possible (e.g. video)
 value - length bytes
 i work
 */
class BreadMote {
private:
    //Used to convert the corresponding type to a char* value for writing to the remote
    void write(unsigned int);
    void write(int);
    void write(bool);
    void write(char);
    void write(const char*, int);
    void write(const char*);
    
    //determines how to handle the most recent message
    void processMessage(char* buffer);
    
    //Reads the corresponding type from the remote
    int fetchSize(char* buffer);
    char fetchByte(char* buffer);
    bool fetchBool(char* buffer);
    const char* fetchString(char* buffer);
    int fetchInt(char* buffer);
    
    
    //the index for buffer reads during fetch calls
    int fetchIndex;
    
    //type of the incoming message (types are defined in BreadMote.cpp
    int type;
    
    //length of the incoming message
    int length;
    
    /**
     Automatically called when first connecting to the app. This is where most components will be added.
     
     You must implement this method.
     */
    void create();
    
    //restores necessary variables to default values to prepare for new message
    void reset();
    
    //convenience method for writing creation message
    void writeCreate(bool b);
    
    
protected:
    
    /**
     Automatically called to read a single byte from your hardware's radio (e.g. your Wi-Fi module via Serial). This will only be called if {@link getAvailableBytes()} returns a value > 0. This method should not be called directly and will be called internally by the BreadMote class.
     
     You must implement this method.
     
     @return An available byte from your hardware's radio
     */
    char readByte();
    
    /**
     Automatically called to check how many bytes are available from your hardware's radio (e.g. your Wi-Fi module via Serial). This method should not be called directly and will be called internally by the BreadMote class.
     
     You must implement this method.
     
     @return The number of bytes available to be read from your hardware's radio
     */
    int getAvailableBytes();
    
    /**
     Automatically called to write bytes to your hardware's radio. This method should not be called directly and will be called internally by the BreadMote class.
     
     You must implement this method.
     
     @param bytes bytes to be written to your hardware's radio
     @param numBytes the length of <code>bytes</code>
     */
    void write(char* bytes, int numBytes);
    
    
public:
    BreadMote();
    
    /**
     Checks to see if there are any messages available to read from your hardware's radio.
     
     This should be called in your hardware's main loop.
     */
    void read();
    
    /**
     Updates a previously created slider or radio group.
     
     @param name the name of the component
     @param value the component's new value
     */
    void update(const char* name, int value);
    
    /**
     Updates a previously created switch, button or checkbox.
     
     @param name the name of the component
     @param value the component's new value
     */
    void update(const char* name, bool value);
    
    /**
     Updates a previously created text field or time picker
     
     @param name the name of the component
     @param value the component's new value
     */
    void update(const char* name, const char* value);
    
    
    /**
     Creates a slider (aka seek bar) on the app which can be used to select from a range of integers.
     
     @param name the slider's name
     @param f a function with only an int as an argument and no return value, e.g. {@code void onSlider(int)}
     @param min minimum slider value
     @param max maximum slider value
     @param value the slider's current value. <code>min <= value <= max</code>
     @see onCommand(const char*, int)
     */
    void addSlider(const char* name, void (*f)(int), int min, int max, int value);
    
    /**
     Creates a switch on the app which can be used to toggle a boolean.
     
     @param name the switch's name
     @param f a function with only a bool as an argument and no return value, e.g. {@code void onSwitch(bool)}
     @param value the switch's current value. <code>true</code> if on, <code>false</code> otherwise
     @see onCommand(const char*, bool)
     */
    void addSwitch(const char* name, void (*f)(bool), bool value);
    
    /**
     Creates a button on the app.
     
     @param name the button's name
     @param f a function with no arguments and no return value, e.g. {@code void onButton()}
     @see onCommand(const char*, bool)
     */
    void addButton(const char* name, void (*f)());
    
    /**
     Creates a check box on the app which can be used to toggle a boolean.
     
     @param name the check box's name
     @param f a function with only a bool as an argument and no return value, e.g. {@code void onCheckBox(bool)}
     @param value the check box's current value. <code>true</code> if checked, <code>false</code> otherwise
     
     @see onCommand(const char*, bool)
     */
    void addCheckBox(const char* name, void (*f)(bool), bool value);
    
    /**
     Creates an editable text field on the app which can be used to send text.
     
     @param name the text field's name
     @param f a function with only a const char* as an argument and no return value, e.g. {@code void onText(const char*)}
     @param value the text field's current text
     
     @see onCommand(const char*, const char*)
     */
    void addTextField(const char* name, void(*f)(const char*), const char* value);
    
    /**
     Creates a text field on the app which can be used to display a value. A label cannot be interacted with by a user.
     
     @param name the label's name. Label names can be formattable (e.g. <code>"Hello %s!"</code>)
     @param value the text displayed by the label. If <code>name</code> is formattable, <code>param</code> will be inserted. Otherwise, <code>param</code> will be displayed next to <code>name</code>
     */
    void addLabel(const char* name, const char* value);
    
    /**
     Creates a time picker on the app which can be used to send time values.
     
     @param name the time picker's name. Note: the time value will be automatically displayed after the name.
     @param f a function with two ints as arguments and no return value, e.g. {@code void onTimePicked(int, int)}
     @param hour the hour displayed by the time picker
     @param minute the minute displayed by the time picker
     
     @see onCommand(const char*, const char*)
     */
    void addTimePicker(const char* name, void(*f)(char, char), char hour, char minute);
    
    /**
     Creates a radio group on the app. A radio group is a group of options where only one option can be selected at a time.
     
     @param name the radio group's name.
     @param f a function with only an as an argument and no return value, e.g. {@code void onRadioGroup(bool)}
     @param options the list of choices
     @param numOptions the number of options. This must match the length of <code>options</code>
     @param selectedOption the currently selected option. <code>0 <= selectedOption <= numOptions</code>
     
     @see onCommand(const char*, int)
     */
    void addRadioGroup(const char* name, void (*f)(int), const char** options, unsigned char numOptions, unsigned char selectedOption);
    
    /**
     Removes the specified component from the app. Note: once a component is removed, it can no longer be updated.
     
     @param name the name of the component to be removed
     */
    void remove(const char* name);
    
    /**
     Enables or disables the specified component on the app. An enabled component can be be interacted with by a user. Note: By default, all components are enabled when created.
     
     @param name the name of the component to be enabled
     @param isEnabled <code>true</code> if the component is enabled, false otherwise
     */
    void setEnabled(const char* name, bool isEnabled);
    
    /**
     Displays a log message on the app. This can be useful for debugging or display error messages to the user.
     
     @param tag used to identify the source of a log message. It usually identifies where the log occurs
     @param message the message you would like logged
     */
    void logError(const char* tag, const char* message);
};


//information required by the remote sent in the header
#define PROTOCOL_VERSION    (char)0
#define HEADER_SIZE         7
#define SIZE_OF_INT         (int)(sizeof(int))
#define SIZE_OF_BOOL        1
#define SIZE_OF_FUNC        sizeof(void(*)())

#define TYPE_HEADER         (char)0     //inbound means header is needed, outbound means message is header
#define TYPE_CREATE         (char)1     //inbound means remote should be created, outbound means start / end of creation
#define TYPE_ERROR          (char)2     //outbound only, used to notify remote of error
#define TYPE_REMOVE         (char)3     //outbound only, used to notify remote to remove component
#define TYPE_ENABLE         (char)4     //outbound only, used to enable/disable a component on the remote
#define TYPE_UPDATE         (char)5

//used during creation
#define TYPE_SLIDER         (char)10
#define TYPE_SWITCH         (char)11
#define TYPE_BUTTON         (char)12
#define TYPE_CHECKBOX       (char)13
#define TYPE_TEXT_FIELD     (char)14
#define TYPE_LABEL          (char)15
#define TYPE_TIME_PICKER    (char)16
#define TYPE_RADIO_GROUP    (char)17

//used internally only for resetting values
#define INVALID             -1

#include "BreadMote.h"

namespace{
    int sizeOf(const char* c_str){
        if (c_str == 0) return 1;
        
        int length = 0;
        while(c_str[length++] != '\0');
        return length;
    }
}

BreadMote::BreadMote(){
    reset();
}

void BreadMote::reset() {
    type = INVALID;
    length = INVALID;
    fetchIndex = 0;
}

//-----------------------------------------------------------------------
//------------------- writing values to char arrays ---------------------
void BreadMote::write(int value){
    char* bytes = static_cast<char*>(static_cast<void*>(&value));
    write(bytes, SIZE_OF_INT);
}

void BreadMote::write(unsigned int value){
    write((int)value);
}

void BreadMote::write(bool value){
    char byte = (char)(value ? 1 : 0);
    write(byte);
}

void BreadMote::write(char value){
    char bytes[1] = {value};
    write(bytes, 1);
}

void BreadMote::write(const char* value, int size){
    if (0 == value) {
        write((char)0);
    } else {
        char* valueCast = const_cast<char*>(value);
        write(valueCast, sizeOf(value));
    }
}

void BreadMote::write(const char* value){
    if (0 == value) {
        write((char)0);
    } else {
        char* valueCast = const_cast<char*>(value);
        write(valueCast, sizeOf(value));
    }
}

//-----------------------------------------------------------------------
//------------------------- creating controls ---------------------------

void BreadMote::addSlider(const char* name, void (*f)(int), int min, int max, int def){
    write(TYPE_SLIDER);
    int nameSize = sizeOf(name);
    write(nameSize + SIZE_OF_INT*3 + SIZE_OF_FUNC);
    write(name, nameSize);
    write((int)f);
    write(min);
    write(max);
    write(def);
}

void BreadMote::addSwitch(const char* name, void (*f)(bool), bool def){
    write(TYPE_SWITCH);
    int nameSize = sizeOf(name);
    write(nameSize + SIZE_OF_BOOL + SIZE_OF_FUNC);
    write(name, nameSize);
    write((int)f);
    write(def);
}

void BreadMote::addButton(const char* name, void (*f)()) {
    write(TYPE_BUTTON);
    int nameSize = sizeOf(name);
    write(nameSize + SIZE_OF_FUNC);
    write(name, nameSize);
    write((int)f);
}

void BreadMote::addCheckBox(const char* name, void (*f)(bool), bool def){
    write(TYPE_CHECKBOX);
    int nameSize = sizeOf(name);
    write(nameSize + SIZE_OF_BOOL + SIZE_OF_FUNC);
    write(name, nameSize);
    write((int)f);
    write(def);
}

void BreadMote::addTextField(const char* name, void(*f)(const char*), const char* value) {
    write(TYPE_TEXT_FIELD);
    int nameSize = sizeOf(name);
    write(nameSize + sizeOf(value) + SIZE_OF_FUNC);
    write(name, nameSize);
    write((int)f);
    write(value);
}

void BreadMote::addLabel(const char* name, const char* value) {
    write(TYPE_LABEL);
    int nameSize = sizeOf(name);
    write(nameSize + sizeOf(value));
    write(name, nameSize);
    write(value);
}

void BreadMote::addTimePicker(const char* name, void(*f)(char, char), char hour, char minute) {
    write(TYPE_TIME_PICKER);
    int nameSize = sizeOf(name);
    write(nameSize + 2 + SIZE_OF_FUNC);
    write(name, nameSize);
    write((int)f);
    write(hour);
    write(minute);
}

void BreadMote::addRadioGroup(const char* name, void (*f)(int), const char** options, unsigned char numOptions, unsigned char def) {
    write(TYPE_RADIO_GROUP);
    int nameSize = sizeOf(name);
    unsigned int size = nameSize + 2 + SIZE_OF_FUNC;
    for(unsigned int i = 0; i < numOptions; i++) {
        size += sizeOf(options[i]);
    }
    write(size);
    write(name, nameSize);
    write((int)f);
    write((char)numOptions);
    for(unsigned int i = 0; i < numOptions; i++) {
        write(options[i]);
    }
    write((char)def);
}

//-----------------------------------------------------------------------
//------------------------- updating controls ---------------------------

void BreadMote::update(const char* name, int value){
    write(TYPE_UPDATE);
    int nameSize = sizeOf(name);
    write(nameSize + SIZE_OF_INT);
    write(name, nameSize);
    write(value);
}

void BreadMote::update(const char* name, bool value){
    write(TYPE_UPDATE);
    int nameSize = sizeOf(name);
    write(nameSize + SIZE_OF_BOOL);
    write(name, nameSize);
    write(value);
}

void BreadMote::update(const char* name, const char* value){
    write(TYPE_UPDATE);
    int nameSize = sizeOf(name);
    write(nameSize + sizeOf(value));
    write(name, nameSize);
    write(value);
}

//-----------------------------------------------------------------------
//------------------------- removing controls ---------------------------

void BreadMote::remove(const char* name){
    write(TYPE_REMOVE);
    int nameSize = sizeOf(name);
    write(nameSize);
    write(name, nameSize);
}

//-----------------------------------------------------------------------
//------------------------- toggling controls ---------------------------
void BreadMote::setEnabled(const char* name, bool isEnabled) {
    write(TYPE_ENABLE);
    int nameSize = sizeOf(name);
    write(nameSize + SIZE_OF_BOOL);
    write(name, nameSize);
    write(isEnabled);
}

//-----------------------------------------------------------------------
//------------------------ user logged errors ---------------------------

void BreadMote::logError(const char* name, const char* value){
    write(TYPE_ERROR);
    int nameSize = sizeOf(name);
    write(nameSize + sizeOf(value));
    write(name, nameSize);
    write(value);
}

//-----------------------------------------------------------------------
//-------------------- handling incoming messages -----------------------

void BreadMote::read() {
    //type
    if(type == INVALID && getAvailableBytes() >= 3){
        type = readByte();
        
        char a = readByte();
        char b = readByte();
        
        length = (b << 8 | ((unsigned char)a));
    }
    
    //value
    if(length != INVALID && getAvailableBytes() >= length){
        char buffer[length];
        for (unsigned int i = 0; i < length; i++) {
            buffer[i] = readByte();
        }
        //do not need to update available bytes
        processMessage(buffer);
        reset();
    }
}

void BreadMote::writeCreate(bool isCreating){
    write(TYPE_CREATE);
    write(SIZE_OF_BOOL);
    write(isCreating);
}


void BreadMote::processMessage(char* buffer) {
    if (type == TYPE_HEADER) {
        //header length is forced to 2 bytes, little endian styles
        //this test assumes sizeof(char) != sizeof(int)
        int test = 1;
        bool isBigEndian = (*(char *)&test != 1);
        
        char header[HEADER_SIZE] = {TYPE_HEADER, HEADER_SIZE - 3, 0, PROTOCOL_VERSION, isBigEndian, SIZE_OF_INT, SIZE_OF_FUNC};
        
        write(header, HEADER_SIZE);
    } else if(type == TYPE_CREATE){
        writeCreate(true);
        create();
        writeCreate(false);
    } else {
        int func = fetchInt(buffer);
        switch(type) {
            case TYPE_SLIDER:
            case TYPE_RADIO_GROUP:{
                int i = fetchInt(buffer);
                ((void(*)(int))func)(i);
                break;
            }break;
            case TYPE_BUTTON:
                ((void(*)())func)();
                break;
            case TYPE_SWITCH:
            case TYPE_CHECKBOX:{
                bool b = fetchBool(buffer);
                ((void(*)(bool))func)(b);
            }                break;
            case TYPE_TEXT_FIELD:{
                const char* text = fetchString(buffer);
                ((void(*)(const char*))func)(text);
            } break;
            case TYPE_TIME_PICKER:{
                char hour = fetchByte(buffer);
                char minute = fetchByte(buffer);
                ((void(*)(char, char))func)(hour, minute);
            }
                break;
        }
    }
}

int BreadMote::fetchInt(char* buffer) {
    int val = 0;
    for (int i = SIZE_OF_INT - 1; i >= 0; i--) {
        val <<= 8;
        val |= (unsigned char)buffer[fetchIndex + i];
    }
    
    fetchIndex += SIZE_OF_INT;
    return val;
}

bool BreadMote::fetchBool(char* buffer) {
    return fetchByte(buffer) > 0;
}

char BreadMote::fetchByte(char* buffer) {
    return buffer[fetchIndex++];
}

const char* BreadMote::fetchString(char* buffer) {
    char* startIndex = buffer + fetchIndex;
    
    while(fetchByte(buffer) != '\0');
    
    return startIndex;
}


#endif /* BreadMote_hpp */
