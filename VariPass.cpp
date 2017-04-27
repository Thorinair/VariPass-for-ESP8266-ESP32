/*
    Library: VariPass for ESP8266
    Programmed by: Thorinair
    Version: v1.0.0
    Description: Provides an API for easily exchanging data with the VariPass (varipass.org) website.
    Usage:  
        First add this library to the "libraries" folder in your Arduino workspace.
        Then, include the library in your program by calling #include <VariPass.h>.
        Please use VariPass.h file as reference for different functions and values.
    Requirements: 
        This library requires you to have an ESP8266 based board.
        Your program needs to be connected to a WiFi for this library to work.
*/

#include "VariPass.h"
#include "ESP8266WiFi.h"

#define HOST "api.varipass.org"

static String splitString(String data, char separator, int index);
static String request(String path, int duration);
static void   varipassWrite(String key, String id, String value, int* status);
static String varipassRead(String key, String id, int* status);


static String splitString(String data, char separator, int index) {
    int found = 0;
    int strIndex[] = {0, -1};
    int maxIndex = data.length() - 1;

    for(int i = 0; i <= maxIndex && found <= index; i++) {
        if(data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i + 1 : i;
        }
    }

    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

static String request(String path, int duration) {
    WiFiClient client;
    if (!client.connect(HOST, 80)) {  
        Serial.println("Error connecting!");
        return "";
    }

    client.print("GET " + path + " HTTP/1.1\r\n" +
                 "Host: " + HOST + "\r\n" + 
                 "Connection: close\r\n\r\n");
    delay(duration);

    String body = "";
    while(client.available()){
        String line = client.readStringUntil('\n');
        if (line.length() == 1) {
            client.readStringUntil('\n');
            body = client.readStringUntil('\n');
            body.remove(body.length() - 1, 1);
            break;
        }
    }

    return body;
}

static void varipassWrite(String key, String id, String value, int* status) {
    String response = request("/?key=" + key + "&action=swrite&id=" + id + "&value=" + value, VARIPASS_DURATION_WRITE);

    if (response == "success")
        *status = VARIPASS_RESULT_SUCCESS;
    else if (response == "error_invalid_key")
        *status = VARIPASS_RESULT_ERROR_INVALID_KEY;
    else if (response == "error_invalid_id")
        *status = VARIPASS_RESULT_ERROR_INVALID_ID;
    else if (response == "error_cooldown")
        *status = VARIPASS_RESULT_ERROR_COOLDOWN;
    else if (response == "error_unconfirmed")
        *status = VARIPASS_RESULT_ERROR_UNCONFIRMED;
    else if (response == "error_banned")
        *status = VARIPASS_RESULT_ERROR_BANNED;
    else if (response == "error_empty_variable")
        *status = VARIPASS_RESULT_ERROR_EMPTY_VARIABLE;
    else if (response == "error_db")
        *status = VARIPASS_RESULT_ERROR_DB;
    else
        *status = VARIPASS_RESULT_ERROR_UNKNOWN;  
}

void varipassWriteInt(String key, String id, long value, int* status) {
    varipassWrite(key, id, String(value), status);
}

void varipassWriteFloat(String key, String id, double value, int* status) {
    varipassWrite(key, id, String(value), status);
}

void varipassWriteBool(String key, String id, bool value, int* status) {
    String boolval = "false";
    if (value)
        boolval = "true";
    varipassWrite(key, id, boolval, status);
}

void varipassWriteString(String key, String id, String value, int* status) {
    varipassWrite(key, id, value, status);
}

static String varipassRead(String key, String id, int* status) {
    String response = request("/?key=" + key + "&action=sread&id=" + id, VARIPASS_DURATION_READ);

    String result = splitString(response, '|', 0);
    if (result == "success") {
        *status = VARIPASS_RESULT_SUCCESS;
        return splitString(response, '|', 1);            
    }
    else {
        if (response == "error_invalid_key")
            *status = VARIPASS_RESULT_ERROR_INVALID_KEY;
        else if (response == "error_invalid_id")
            *status = VARIPASS_RESULT_ERROR_INVALID_ID;
        else if (response == "error_cooldown")
            *status = VARIPASS_RESULT_ERROR_COOLDOWN;
        else if (response == "error_unconfirmed")
            *status = VARIPASS_RESULT_ERROR_UNCONFIRMED;
        else if (response == "error_banned")
            *status = VARIPASS_RESULT_ERROR_BANNED;
        else if (response == "error_empty_variable")
            *status = VARIPASS_RESULT_ERROR_EMPTY_VARIABLE;
        else if (response == "error_db")
            *status = VARIPASS_RESULT_ERROR_DB;
        else
            *status = VARIPASS_RESULT_ERROR_UNKNOWN;  

        return "";   
    }            
}

long varipassReadInt(String key, String id, int* status) {
    return atol(varipassRead(key, id, status).c_str());
}

double varipassReadFloat(String key, String id, int* status) {
    return atof(varipassRead(key, id, status).c_str());
}

bool varipassReadBool(String key, String id, int* status) {
    String value = varipassRead(key, id, status);
    if (value == "true")
        return true;
    else
        return false;
}

String varipassReadString(String key, String id, int* status) {
    return varipassRead(key, id, status);
}
