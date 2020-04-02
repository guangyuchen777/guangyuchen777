/******************************************************************************
   Example of the OOCSI-ESP library connecting to WiFi and sending messages
   over OOCSI. Designed to work with the Processing OOCSI receiver example
   that is provided in the same directory
 ******************************************************************************/
const int touchPin = 4; 
const int ledPin = 17;
// change with your threshold value
const int threshold = 20;
// variable for storing the touch pin value 
int touchValue;

#include "OOCSI.h"

// use this if you want the OOCSI-ESP library to manage the connection to the Wifi
// SSID of your Wifi network, the library currently does not support WPA2 Enterprise networks
const char* ssid = "It Hurts When IP.";
// Password of your Wifi network.
const char* password = "chouhuashuoqiantou";

// name for connecting with OOCSI (unique handle)ESP_OOCSI_Guang_SENDER
const char* OOCSIName = "ESP_OOCSI_GUANG_SENDER";
// put the adress of your OOCSI server here, can be URL or IP address string
const char* hostserver = "oocsi.id.tue.nl";

// OOCSI reference for the entire sketch
OOCSI oocsi = OOCSI();

// put your setup code here, to run once:
void setup() {
  Serial.begin(115200);
  delay(500);
  // output OOCSI activity on the built-in LED
  pinMode(ledPin, OUTPUT);
  //oocsi.setActivityLEDPin(ledPin);

  // use this to switch off logging to Serial
  // oocsi.setLogging(false);

  // setting up OOCSI. processOOCSI is the name of the function to call when receiving messages, can be a random function name
  // connect wifi and OOCSI to the server
  oocsi.connect(OOCSIName, hostserver, ssid, password, processOOCSI);

}

// put your main code here, to run repeatedly:
void loop() {
   // read the state of the pushbutton value:
  touchValue = touchRead(touchPin);
  Serial.print(touchValue);
  // check if the touchValue is below the threshold
  // if it is, set ledPin to HIGH
  if(touchValue < threshold){
    // turn LED on
    digitalWrite(ledPin, HIGH);
    Serial.println(" - LED on");
  }
  else{
    // turn LED off
    digitalWrite(ledPin, LOW);
    Serial.println(" - LED off");
  }
  delay(500);
  
  // create a new message
  oocsi.newMessage("esp-Guangchannel");

  // add data (primitive data types int, float, long, string)
  // the labels such as "count" or "timestamp" are completely free to choose
  oocsi.addInt("touchValue", touchRead(touchPin));


  // this command will send the message; don't forget to call this after creating a message
  oocsi.sendMessage();

  // prints out the raw message (how it is sent to the OOCSI server)
  // oocsi.printSendMessage();

  // needs to be checked in order for OOCSI to process incoming data.
  oocsi.check();
  delay(500);
}

void processOOCSI() {
  Serial.print("\t touchValue: ");
  Serial.print(oocsi.getInt("touchValue", touchRead(touchPin)));
  
  Serial.print("\t sender: ");
  Serial.print(oocsi.getSender());
  Serial.print("\t recipient: ");
  Serial.print(oocsi.getRecipient());
  Serial.print("\t Timestamp: ");
  Serial.print(oocsi.getTimeStamp());
  Serial.println();
}
