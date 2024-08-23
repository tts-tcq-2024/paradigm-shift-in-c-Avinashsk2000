#include <stdio.h>
#include <assert.h>

#define ERROR_TEMP "Temperature out of range!\n"
#define ERROR_SOC "State of Charge out of range!\n"
#define ERROR_CHARGE "Charge Rate out of range!\n"

int checkAndPrint(float value, float min, float max, const char* errorMessage) {
    if (value < min || value > max) {
        printf("%s", errorMessage);
        return 0;
    }
    return 1;
}

int batteryIsOk(float temperature, float soc, float chargeRate) {
    int isTemperatureOk = checkAndPrint(temperature, 0, 45, ERROR_TEMP);
    int isSocOk = checkAndPrint(soc, 20, 80, ERROR_SOC);
    int isChargeRateOk = checkAndPrint(chargeRate, 0, 0.8, ERROR_CHARGE);

    return isTemperatureOk && isSocOk && isChargeRateOk;
}

int main() {
    assert(batteryIsOk(25, 70, 0.7));
    assert(!batteryIsOk(50, 85, 0));
    //Test case for valid
    assert(batteryIsOk(0, 20, 0.0));     // Lower boundary of all values
    assert(batteryIsOk(45, 80, 0.8));    // Upper boundary of all value
    // Test cases for invalid temp
    assert(!batteryIsOk(-1, 70, 0.7));   // Temperature below range
    assert(!batteryIsOk(46, 70, 0.7));   // Temperature above range
    // Test cases for invalid SOC
    assert(!batteryIsOk(25, 19, 0.7));   // SOC below range
    assert(!batteryIsOk(25, 81, 0.7));   // SOC above range
    // Test cases for invalid charge rate
    assert(!batteryIsOk(25, 70, 0.9));   // Charge rate above range
    // Test cases for invalid combinations
    assert(!batteryIsOk(-1, 19, 0.9));   // Temperature and SOC below range
    assert(!batteryIsOk(46, 81, 0.9));   // Temperature and SOC above range
    assert(!batteryIsOk(25, 70, 1.0));   // Charge rate above range, within valid temperature and SOC
    // Test cases for edge values
    assert(!batteryIsOk(0, 19, 0.7));    // Lower boundary for temperature, SOC below range
    assert(!batteryIsOk(45, 81, 0.8));   // Upper boundary for temperature, SOC above range
    assert(batteryIsOk(25, 70, 0.8));    // Valid at upper boundary of charge rate
    assert(batteryIsOk(25, 70, 0.0));    // Valid at lower boundary of charge rate
}
