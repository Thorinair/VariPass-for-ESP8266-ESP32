# VariPass Library for ESP8266 and ESP32
VariPass library for ESP8266 allows you to easily read and write data to the [VariPass](https://varipass.org) website. The library should be used with the Arduino IDE.

## Available Functions
The following functions are used to write data to VariPass. You should use the one which fits your variable type.
```cpp
void varipassWriteInt   (String key, String id, long   value, int* result);
void varipassWriteFloat (String key, String id, double value, int* result, char decimals);
void varipassWriteBool  (String key, String id, bool   value, int* result);
void varipassWriteString(String key, String id, String value, int* result);
```

The following functions are used to read data from VariPass. You should use the one which fits your variable type.
```cpp
long   varipassReadInt   (String key, String id, int* result);
double varipassReadFloat (String key, String id, int* result);
bool   varipassReadBool  (String key, String id, int* result);
String varipassReadString(String key, String id, int* result);
```

The following function is used to retrieve the latest values of all variables from VariPass, returned as an array. All variables will store their IDs and values in char arrays, which should then be parsed to types as needed.
```cpp
Variable * varipassLatest(String key, int* count, int* result);
```

The following function converts the result code to a readable description as string.
```cpp
String varipassGetResultDescription(int result);
```

## Examples
Here are a few simple examples how to read and write data. For more detailed descriptions and comments, please check the examples in the examples folder.

### Writing Data
```cpp
int result;
varipassWriteInt(key, varid, value, &result);

if (result == VARIPASS_RESULT_SUCCESS)
    Serial.println("Value successfully written! Check the Dashboard.");
else
    Serial.println("An error has occured writing the value! " + varipassGetResultDescription(result));
```

### Reading Data
```cpp
int result;
int value = varipassReadInt(key, varid, &result);

if (result == VARIPASS_RESULT_SUCCESS)
    Serial.println("Value successfully read! Value is: " + String(value));
else
    Serial.println("An error has occured reading the value! " + varipassGetResultDescription(result));
```

### Retrieve Latest Data
```cpp
int result;
int count;
Variable *variables = varipassLatest(key, &count, &result);

if (result == VARIPASS_RESULT_SUCCESS) {
    Serial.println("Count: " + String(count));
    for (int i = 0; i < count; i++)
        Serial.println("  " + String(variables[i].id) + ": " + String(variables[i].value));
}
else {
    Serial.println("An error has occured reading the value! " + varipassGetResultDescription(result));
}

free(variables);
```