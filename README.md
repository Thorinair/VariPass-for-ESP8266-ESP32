# VariPass Library For ESP8266
VariPass library for ESP8266 allows you to easily read and write data to the [VariPass](https://varipass.org) website. The library should be used with the Arduino IDE.

## Available Functions
The following functions are used to write data to VariPass. You should use the one which fits your variable type.
```
void varipassWriteInt   (String key, String id, long   value, int* result);
void varipassWriteFloat (String key, String id, double value, int* result, char decimals);
void varipassWriteBool  (String key, String id, bool   value, int* result);
void varipassWriteString(String key, String id, String value, int* result);
```

The following functions are used to read data from VariPass. You should use the one which fits your variable type.
```
long   varipassReadInt   (String key, String id, int* result);
double varipassReadFloat (String key, String id, int* result);
bool   varipassReadBool  (String key, String id, int* result);
String varipassReadString(String key, String id, int* result);
```

The following function converts the result code to a readable description as string.
```
String varipassGetResultDescription(int result);
```

## Examples
Here are a few simple examples how to read and write data. For more detailed descriptions and comments, please check the examples in the examples folder.

### Writing Data
```
int result;
varipassWriteInt(key, varid, value, &result);

if (result == VARIPASS_RESULT_SUCCESS)
    Serial.println("Value successfully written! Check the Dashboard.");
else
    Serial.println("An error has occured writing the value! " + varipassGetResultDescription(result));
```

### Reading Data
```
int result;
int value = varipassReadInt(key, varid, &result);

if (result == VARIPASS_RESULT_SUCCESS)
    Serial.println("Value successfully read! Value is: " + String(value));
else
    Serial.println("An error has occured reading the value! " + varipassGetResultDescription(result));
```