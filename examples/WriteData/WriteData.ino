/*
    Example: WriteData
    Description: This example shows you how to write data to VariPass.
*/

#ifdef ESP8266
    #include <ESP8266WiFi.h>
#elif ESP32
    #include <WiFi.h>
#endif
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

// Variable storing the value which will be written to VariPass.
int value = 0;

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
    
    // Send variable value to VariPass.
    varipassWriteInt(key, varid, value, &result);

    // Check whether the writing was successful and handle accordingly.
    if (result == VARIPASS_RESULT_SUCCESS)
        Serial.println("Value successfully written! Check the Dashboard.");
    else
        Serial.println("An error has occured writing the value! " + varipassGetResultDescription(result));

    // Increment the value for next loop.
    value++;
    
    delay(2000);
}
