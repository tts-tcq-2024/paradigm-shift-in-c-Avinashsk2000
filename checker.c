#include <stdio.h>
#include <assert.h>

#define ERROR_TEMP "Temperature out of range!\n"
#define ERROR_SOC "State of Charge out of range!\n"
#define ERROR_CHARGE "Charge Rate out of range!\n"
#define WARNING_TEMP_LOW "Warning: Approaching lower temperature limit\n"
#define WARNING_TEMP_HIGH "Warning: Approaching upper temperature limit\n"
#define WARNING_SOC_LOW "Warning: Approaching discharge\n"
#define WARNING_SOC_HIGH "Warning: Approaching charge-peak\n"
#define WARNING_CHARGE_LOW "Warning: Approaching lower charge rate limit\n"
#define WARNING_CHARGE_HIGH "Warning: Approaching upper charge rate limit\n"

float tolerance = 0.05;  // 5% tolerance

// Function to print errors
int checkOutOfRange(float value, float min, float max, const char* errorMessage) {
    if (value < min || value > max) {
        printf("%s", errorMessage);
        return 1;  // Out of range
    }
    return 0;  // Within range
}

// Function to print low warnings
void printLowWarning(float value, float min, const char* warningMessage) {
    if (value <= min + (tolerance * (min))) {
        printf("%s", warningMessage);
    }
}

// Function to print high warnings
void printHighWarning(float value, float max, const char* warningMessage) {
    if (value >= max - (tolerance * max)) {
        printf("%s", warningMessage);
    }
}

// Function to handle range and warnings
int checkValue(float value, float min, float max, const char* errorMessage, const char* warnLow, const char* warnHigh) {
    if (checkOutOfRange(value, min, max, errorMessage)) {
        return 0;  // If out of range, skip warnings
    }

    printLowWarning(value, min, warnLow);  // Check and print low warning
    printHighWarning(value, max, warnHigh);  // Check and print high warning
    return 1;  // Value within range
}

// Function to check battery health
int batteryIsOk(float temperature, float soc, float chargeRate) {
    int temperatureStatus = checkValue(temperature, 0, 45, ERROR_TEMP, WARNING_TEMP_LOW, WARNING_TEMP_HIGH);
    int socStatus = checkValue(soc, 20, 80, ERROR_SOC, WARNING_SOC_LOW, WARNING_SOC_HIGH);
    int chargeRateStatus = checkValue(chargeRate, 0, 0.8, ERROR_CHARGE, WARNING_CHARGE_LOW, WARNING_CHARGE_HIGH);

    return temperatureStatus && socStatus && chargeRateStatus;
}

int main() {
    // Valid cases
    assert(batteryIsOk(25, 70, 0.7));
    assert(batteryIsOk(0, 20, 0.0));
    assert(batteryIsOk(45, 80, 0.8));

    // Test cases for invalid temperature
    assert(!batteryIsOk(-1, 70, 0.7));
    assert(!batteryIsOk(46, 70, 0.7));

    // Test cases for invalid SOC
    assert(!batteryIsOk(25, 19, 0.7));
    assert(!batteryIsOk(25, 81, 0.7));

    // Test cases for invalid charge rate
    assert(!batteryIsOk(25, 70, 0.9));

    // Test cases for invalid combinations
    assert(!batteryIsOk(-1, 19, 0.9));
    assert(!batteryIsOk(46, 81, 0.9));
    assert(!batteryIsOk(25, 70, 1.0));

    // Edge cases
    assert(!batteryIsOk(0, 19, 0.7));
    assert(!batteryIsOk(45, 81, 0.8));
    assert(batteryIsOk(25, 70, 0.8));
    assert(batteryIsOk(25, 70, 0.0));

    return 0;
}
