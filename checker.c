#include <stdio.h>
#include <assert.h>

#define ERROR_TEMP "Temperature out of range!\n"  
#define ERROR_SOC "State of Charge out of range!\n"
#define ERROR_CHARGE "Charge Rate out of range!\n"

// Function to check if the value is within the specified range
int CheckValue(float value, float min, float max) {
    return (value >= min && value <= max);
}

// Function to print the error message
void PrintErrorMessage(const char* errormessage) {
    printf("%s", errormessage);
}

int BatteryIsOk(float temperature, float soc, float chargeRate) {
    // Array of checks and corresponding error messages
    float values[] = {temperature, soc, chargeRate};
    float minValues[] = {0, 20, 0};
    float maxValues[] = {45, 80, 0.8};
    const char* errorMessages[] = {ERROR_TEMP, ERROR_SOC, ERROR_CHARGE};
    
    int result = 1; // Assume all checks are okay initially
    
    for (int i = 0; i < 3; i++) {
        if (!CheckValue(values[i], minValues[i], maxValues[i])) {
            PrintErrorMessage(errorMessages[i]);
            result = 0; // Set result to 0 if any check fails
        }
    }
    
    return result;
}

int main() {
    testValidCases();
    testInvalidTemperatureCases();
    testInvalidSocCases();
    testInvalidChargeRateCases();
    testInvalidCombinations();
    testEdgeCases();
}

// Function to test valid cases
void testValidCases() {
    assert(batteryIsOk(25, 70, 0.7));
    assert(batteryIsOk(0, 20, 0.0));  // Lower boundary of all values
    assert(batteryIsOk(45, 80, 0.8)); // Upper boundary of all values
    assert(batteryIsOk(25, 70, 0.8)); // Valid at upper boundary of charge rate
    assert(batteryIsOk(25, 70, 0.0)); // Valid at lower boundary of charge rate
}

// Function to test invalid temperature cases
void testInvalidTemperatureCases() {
    assert(!batteryIsOk(-1, 70, 0.7)); // Temperature below range
    assert(!batteryIsOk(46, 70, 0.7)); // Temperature above range
}

// Function to test invalid SOC cases
void testInvalidSocCases() {
    assert(!batteryIsOk(25, 19, 0.7)); // SOC below range
    assert(!batteryIsOk(25, 81, 0.7)); // SOC above range
}

// Function to test invalid charge rate cases
void testInvalidChargeRateCases() {
    assert(!batteryIsOk(25, 70, 0.9)); // Charge rate above range
}

// Function to test invalid combinations
void testInvalidCombinations() {
    assert(!batteryIsOk(-1, 19, 0.9)); // Temperature and SOC below range
    assert(!batteryIsOk(46, 81, 0.9)); // Temperature and SOC above range
    assert(!batteryIsOk(25, 70, 1.0)); // Charge rate above range, within valid temperature and SOC
}

// Function to test edge cases
void testEdgeCases() {
    assert(!batteryIsOk(0, 19, 0.7));  // Lower boundary for temperature, SOC below range
    assert(!batteryIsOk(45, 81, 0.8)); // Upper boundary for temperature, SOC above range
}

