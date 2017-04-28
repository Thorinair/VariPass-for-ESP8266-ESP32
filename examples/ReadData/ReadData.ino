/*
    Example: ReadData
    Description: This example shows you how to read data from VariPass.
*/

#include "ESP8266WiFi.h"
#include <VariPass.h>

// WiFi settings
const char* ssid     = "YourWifi";  // Your WiFi SSID
const char* password = "password";  // Your WiFi password

// You will need to register on VariPass (https://varipass.org) to proceed.
// Once you have registered and confirmed your email, add a variable to your
// Dashboard by pressing the plus sign. You will need the info available by 
// pressing the little chain icon on the newly added variable.
String key    = "Tl4g8ZQ0MFcBmQfO"; // Your VariPass API key.
String varid  = "TUWmbh3U";         // Your VariPass variable ID.

void setup() {
    Serial.begin(115200);

    // Connect to the WiFi network.
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("Successfully connected to the WiFi network!");
}

void loop() {
    // Variable which will be storing the result code.
    int result;
    
    // Read variable value from VariPass.
    int value = varipassReadInt(key, varid, &result);

    // Check whether the reading was successful and handle accordingly.
    if (result == VARIPASS_RESULT_SUCCESS)
        Serial.println("Value successfully read! Value is: " + String(value));
    else
        Serial.println("An error has occured reading the value! " + varipassGetResultDescription(result));
    
    delay(2000);
}
