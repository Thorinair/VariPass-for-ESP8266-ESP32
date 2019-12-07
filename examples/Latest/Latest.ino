/*
    Example: Latest
    Description: This example shows you how to retrieve the latest data from VariPass.
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
String key = "Tl4g8ZQ0MFcBmQfO"; // Your VariPass API key.

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
    // Variable which will be storing the number of variables.
    int count;
    
    // Read the latest variable values from VariPass and store them in variables array.
    Variable *variables = varipassLatest(key, &count, &result);

    // Check whether the action was successful and handle accordingly.
    if (result == VARIPASS_RESULT_SUCCESS) {
        // Print the number of variables.
        Serial.println("Count: " + String(count));
        // Print each variable's ID and value.
        for (int i = 0; i < count; i++)
            Serial.println("  " + String(variables[i].id) + ": " + String(variables[i].value));
    }
    else {
        Serial.println("An error has occured reading the value! " + varipassGetResultDescription(result));
    }

    // Free the memory after you are done.
    free(variables);
    
    delay(2000);
}
