/*
    Library: VariPass for ESP8266
    Programmed by: Thorinair
    Version: v1.1.0
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
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define HOST "http://api.varipass.org"

static String splitString(String data, char separator, int index);
static String request(String path);
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

static String request(String path) {
	if (WiFi.status() == WL_CONNECTED) {
		HTTPClient http;

		http.begin(HOST + path);

		int httpCode = http.GET();
		if (httpCode != 200)
	        return "error_connect";

		String body = http.getString();
		http.end();

	    return body;
	}
	else {
		return "error_wifi";
	}
}

static void varipassWrite(String key, String id, String value, int* result) {
    String response = request("/?key=" + key + "&action=swrite&id=" + id + "&value=" + value);

    if (response == "success")
        *result = VARIPASS_RESULT_SUCCESS;
    else if (response == "error_invalid_key")
        *result = VARIPASS_RESULT_ERROR_INVALID_KEY;
    else if (response == "error_invalid_id")
        *result = VARIPASS_RESULT_ERROR_INVALID_ID;
    else if (response == "error_cooldown")
        *result = VARIPASS_RESULT_ERROR_COOLDOWN;
    else if (response == "error_unconfirmed")
        *result = VARIPASS_RESULT_ERROR_UNCONFIRMED;
    else if (response == "error_banned")
        *result = VARIPASS_RESULT_ERROR_BANNED;
    else if (response == "error_empty_variable")
        *result = VARIPASS_RESULT_ERROR_EMPTY_VARIABLE;
    else if (response == "error_db")
        *result = VARIPASS_RESULT_ERROR_DB;
    else if (response == "error_wifi")
        *result = VARIPASS_RESULT_ERROR_WIFI;
    else if (response == "error_connect")
        *result = VARIPASS_RESULT_ERROR_CONNECT;
    else
        *result = VARIPASS_RESULT_ERROR_UNKNOWN;

}

void varipassWriteInt(String key, String id, long value, int* result) {
    varipassWrite(key, id, String(value), result);
}

void varipassWriteFloat(String key, String id, double value, int* result, char decimals) {
    varipassWrite(key, id, String(value, decimals), result);
}

void varipassWriteBool(String key, String id, bool value, int* result) {
    String boolval = "false";
    if (value)
        boolval = "true";
    varipassWrite(key, id, boolval, result);
}

void varipassWriteString(String key, String id, String value, int* result) {
    varipassWrite(key, id, value, result);
}

static String varipassRead(String key, String id, int* result) {
    String response = request("/?key=" + key + "&action=sread&id=" + id);

    String responseResult = splitString(response, '|', 0);
    if (responseResult == "success") {
        *result = VARIPASS_RESULT_SUCCESS;
        return splitString(response, '|', 1);            
    }
    else {
        if (response == "error_invalid_key")
            *result = VARIPASS_RESULT_ERROR_INVALID_KEY;
        else if (response == "error_invalid_id")
            *result = VARIPASS_RESULT_ERROR_INVALID_ID;
        else if (response == "error_cooldown")
            *result = VARIPASS_RESULT_ERROR_COOLDOWN;
        else if (response == "error_unconfirmed")
            *result = VARIPASS_RESULT_ERROR_UNCONFIRMED;
        else if (response == "error_banned")
            *result = VARIPASS_RESULT_ERROR_BANNED;
        else if (response == "error_empty_variable")
            *result = VARIPASS_RESULT_ERROR_EMPTY_VARIABLE;
        else if (response == "error_db")
            *result = VARIPASS_RESULT_ERROR_DB;
	    else if (response == "error_wifi")
	        *result = VARIPASS_RESULT_ERROR_WIFI;
	    else if (response == "error_connect")
	        *result = VARIPASS_RESULT_ERROR_CONNECT;
        else
            *result = VARIPASS_RESULT_ERROR_UNKNOWN;  


        return "";   
    }            
}

long varipassReadInt(String key, String id, int* result) {
    return atol(varipassRead(key, id, result).c_str());
}

double varipassReadFloat(String key, String id, int* result) {
    return atof(varipassRead(key, id, result).c_str());
}

bool varipassReadBool(String key, String id, int* result) {
    String value = varipassRead(key, id, result);
    if (value == "true")
        return true;
    else
        return false;
}

String varipassReadString(String key, String id, int* result) {
    return varipassRead(key, id, result);
}

String varipassGetResultDescription(int result) {
    String description;

    switch (result) {
        case VARIPASS_RESULT_ERROR_UNKNOWN:
            description = "An unknown error has occurred. Usually caused by timeouts.";
            break;

        case VARIPASS_RESULT_SUCCESS:
            description = "Data has been successfully written or read from VariPass.";
            break;

        case VARIPASS_RESULT_ERROR_INVALID_KEY:
            description = "Your API key is invalid.";
            break;

        case VARIPASS_RESULT_ERROR_INVALID_ID:
            description = "Your variable ID is invalid.";
            break;

        case VARIPASS_RESULT_ERROR_COOLDOWN:
            description = "You are sending data too often. Check the cooldown for this variable on your Dashboard.";
            break;

        case VARIPASS_RESULT_ERROR_UNCONFIRMED:
            description = "You email address is not yet confirmed. Click the link you have received in your inbox.";
            break;

        case VARIPASS_RESULT_ERROR_BANNED:
            description = "Your account has been banned from VariPass.";
            break;

        case VARIPASS_RESULT_ERROR_EMPTY_VARIABLE:
            description = "The variable you are trying to read or write to is empty. Please contact support.";
            break;

        case VARIPASS_RESULT_ERROR_DB:
            description = "There is an error with the VariPass database. Please contact support.";
            break;

        case VARIPASS_RESULT_ERROR_WIFI:
            description = "The WiFi is not connected.";
            break;

        case VARIPASS_RESULT_ERROR_CONNECT:
            description = "There was an error while connecting to VariPass.";
            break;
    }

    return description;
}