//==============================================================================
//    E - R A D I O N I C A . C O M,  H.Kolomana 6/A, Djakovo 31400, Croatia
//==============================================================================
// Project   :  Varipass library for ESP8266 by Thorinair
// File      :  Varipass Write Float example
// Author    :  e-radionica.com 2017
// Licence   :  Open-source !
//==============================================================================
//==============================================================================
// Use with Croduino NOVA(ESP8266) to send data to Varipass.org
// You will need a Varipass.org account. Create it here:
// https://varipass.org/register/
// Varipass is online service for Internet of Things objects used to store
// and access data remotely via internet.
// Varipass is project by Thorinair and all credits go to him.
// Library written by Thorinair: https://github.com/Thorinair/VariPass-for-ESP8266
// You will need set ESP8266 board definition in Arduino IDE as well.
// Check the Varipass tutorial here:
// *varipass-tut-link-goes-here*
//
// e-radionica.com provided examples for this library
// If any questions, just contact techsupport@e-radionica.com
//==============================================================================

#include "ESP8266WiFi.h"
#include <VariPass.h>

const char* ssid     = "HUAWEI-Q4OG0D";  // enter your WiFi SSID
const char* password = "8ZDMQngx"; // enter you WiFi password

// At this point, you will need to add variable to your Varipass Dashboard.
// It's simple to do, just click the + button and enter data

// This is your unique ID key. You can find it by clicking chain icon
// on your new created variable
String myVaripassKey = "t3b0EoUrYEdF0KnB";

// Just below the ID value, you will find ID value. Copy it here as well
String varID = "GDBDCc3j";

float var = 22.32; // variable for storing data
int varipassResponseStatus; // storing Varipass response to your request

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password); // connect to WiFi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("Successfully connected to WiFi network! This is local IP address: ");
  Serial.println(WiFi.localIP()); // ispisuje lokalnu WiFi adresu NOVE
}

void loop() {

  varipassWriteFloat(myVaripassKey, varID, var, &varipassResponseStatus);

  Serial.println(handleResponse(varipassResponseStatus));

  delay(2500);
  var++;
}

