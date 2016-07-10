###Communication Protocol

General Info:

* The interaction must be able to support multiple connects and disconnects without requiring a hardware restart.
* All messages follow Type-Length-Value format.
* Strings are always variable length and interpreted as C strings (null terminating char*)
* All length fields received by the hardware are 2 bytes
* Endianness and integer size on your hardware are taken care of thanks to the HEADER message (described below). This means you do not need to read/write integers in a certain endianness or at a certain length.
* Function pointers are intepreted as ints

**Hardware --> App messages**

HEADER - the first message to be sent in the transaction. Header's length field must be formatted in little endian and be two bytes. This is the only message with an endianness or length requirement.
* Type - 0
* Length - 4
* Value - byte: protocol version, byte: is big endian, byte: sizeOf(int), byte: sizeOf(function)

CREATE - indicates the start and end of app control customization
* Type - 1
* Length - 1
* Value - boolean: true if creation should begin, false when completed

SLIDER - add a slider to the app
* Type - 10
* Length - sizeOf(string) + 4 * sizeOf(int)
* Value - string: name, int: funcPtr, int: min, int: max, int: initial value

SWITCH - add a switch to the app     
* Type - 11
* Length - sizeOf(string) + 1 + sizeof(int)
* Value - string: name, int: funcPtr, boolean: initially on/off

BUTTON - add a button to the app
* Type - 12
* Length - sizeOf(string) + sizeof(int)
* Value - string: name, int: funcPtr

CHECKBOX - add a checkbox to the app  
* Type - 13
* Length - sizeOf(string) + 1 + sizeof(int)
* Value - string: name, int: funcPtr, boolean: initially on/off

TEXT_FIELD - add a textfield to the app
* Type - 14
* Length - sizeOf(string) + sizeof(int) + sizeOf(string) 
* Value - string: name, int: funcPtr, string: initial text

LABEL - add a label to the app
* Type - 15
* Length - sizeOf(string) + sizeOf(string)
* Value - string: name, string: intiail value

TIME_PICKER - add a time picker to the app
* Type - 16
* Length - sizeOf(string) + 2 + sizeof(int)
* Value - string: name, int: funcPtr, byte: hour, byte: minute

RADIO_GROUP - add a radio group to the app
* Type - 17
* Length  - sizeOf(string) + sizeOf(int) + 2 + (number of options) * sizeOf(string)
* Value - string: name, int: funcPtr, byte: number of options, N strings: option1...optionN, byte: initial option index

ERROR - display an error message on the app
* Type - 2
* Length - sizeOf(string) + sizeOf(string)
* Value - string: tag, string: message

REMOVE - removes a control from the app
* TYPE - 3
* Length - sizeOf(string)
* Value - string: name of the control

ENABLE - enables or disables a control in the app. All controls are enables by default when added
* TYPE - 4
* Length - sizeOf(string) + 1
* Value - string: name, boolean: true if enabled, false otherwise

UPDATE - update a control's value
* Type - 5
* Length - sizeOf(string) + (1 | sizeOf(int) | sizeOf(string))
* Value - string: name, (boolean | int | string): value

**App --> Hardware messages**

HEADER - the first message to be sent in the transaction. Indicates a request for the header
* Type - 0
* Length - 0
* Value - none

SLIDER - a slider value change from user interaction
* Type - 10
* Length - 2 * sizeOf(int)
* Value - int: funcPtr, int: value

SWITCH - a switch value change from user interaction
 
* Type - 11
* Length - sizeOf(int) + 1
* Value - int: funcPtr, boolean: value

BUTTON - a button press from user interaction
* Type - 12
* Length - sizeOf(int) + 1
* Value - int: funcPtr, boolean: true

CHECKBOX - a checkbox value change from user interaction
* Type - 13
* Length - sizeOf(int) + 1
* Value - int: funcPtr,boolean: value

TEXT_FIELD - a text field value change from user interaction
* Type - 14
* Length - sizeOf(int) +sizeOf(string)
* Value - int: funcPtr,string: value

TIME_PICKER - a time picker value change from user interaction
* Type - 16
* Length - sizeOf(int) + 2
* Value - int: funcPtr, byte: hour, byte: minute

RADIO_GROUP - a radio group value change from user interaction
* Type - 17
* Length - 2 * sizeOf(int)
* Value - int: funcPtr, int: selected index

**Example communication used in blink**
Hardware specs: little endian and 2 byte size int (e.g. Arduino)

    //initial messages
    <-- HEADER		{0, 0, 0}
    --> HEADER		{0, 3, 0, 1, 0, 2}
    //create is requested by app
    <-- CREATE		{1, 1, 0, 1}
    --> CREATE		{1, 1, 0, 1}
    --> BUTTON		{12, 6, 'B', 'l', 'i', 'n', 'k', '\0'}
    --> CREATE		{1, 1, 9, 0}
    //after creation, some time passes before the user presses the button in the app
    <-- BUTTON		{12, 1, 0, 1}
