#ifndef VARIPASS

#define VARIPASS

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

// Different results returned by the API methods.
#define VARIPASS_RESULT_ERROR_UNKNOWN        -1
#define VARIPASS_RESULT_SUCCESS              0
#define VARIPASS_RESULT_ERROR_INVALID_KEY    1
#define VARIPASS_RESULT_ERROR_INVALID_ID     2
#define VARIPASS_RESULT_ERROR_COOLDOWN       3
#define VARIPASS_RESULT_ERROR_UNCONFIRMED    4
#define VARIPASS_RESULT_ERROR_BANNED         5
#define VARIPASS_RESULT_ERROR_EMPTY_VARIABLE 6
#define VARIPASS_RESULT_ERROR_DB             7

// Duration of a single request.
#define VARIPASS_DURATION_WRITE 100
#define VARIPASS_DURATION_READ  10

/*
 * Functions used to send data to VariPass.
 *
 * key:    User's API key which can be found on the website.
 * id:     ID of the variable to be written to.
 * value:  Value to write. Different types depending on function.
 * status: Reference to a status variable. Used to save the API results.
 */
void varipassWriteInt   (String key, String id, long   value, int* status);
void varipassWriteFloat (String key, String id, double value, int* status);
void varipassWriteBool  (String key, String id, bool   value, int* status);
void varipassWriteString(String key, String id, String value, int* status);

/*
 * Functions used to read data from VariPass.
 *
 * key:    User's API key which can be found on the website.
 * id:     ID of the variable to be written to.
 * status: Reference to a status variable. Used to save the API results.
 *
 * return: Value from VariPass. Different types depending on function.
 */
long   varipassReadInt   (String key, String id, int* status);
double varipassReadFloat (String key, String id, int* status);
bool   varipassReadBool  (String key, String id, int* status);
String varipassReadString(String key, String id, int* status);

#endif
