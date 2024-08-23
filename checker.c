#include <stdio.h>
#include <assert.h>

/* We could have added these printf values directly inside the functions,
but as we are in need of a pure function. 
it's better to use macros so both the functions become independent.
*/
#define ERROR_TEMP "Temperature out of range!\n"  
#define ERROR_SOC "State of Charge out of range!\n"
#define ERROR_CHARGE "Charge Rate out of range!\n"

int CheckAndPrint(float value, float min, float max, const char* errormessage) {
    if (value < min || value > max) {
        printf("%s", errormessage);
        return 0;
    }
    return 1;
}

int BatteryIsOk(float temperature, float soc, float chargeRate) {
    int isTemperatureOk = CheckAndPrint(temperature, 0, 45, ERROR_TEMP);
    int isSocOk = CheckAndPrint(soc, 20, 80, ERROR_SOC);
    int isChargeRateOk = CheckAndPrint(chargeRate, 0, 0.8, ERROR_CHARGE);

    return isTemperatureOk && isSocOk && isChargeRateOk;
}

int main() {
    assert(BatteryIsOk(25, 70, 0.7));
    assert(!BatteryIsOk(50, 85, 0));
    //Test case for valid
    assert(BatteryIsOk(0, 20, 0.0));     // Lower boundary of all values
    assert(BatteryIsOk(45, 80, 0.8));    // Upper boundary of all value
    // Test cases for invalid temp
    assert(!BatteryIsOk(-1, 70, 0.7));   // Temperature below range
    assert(!BatteryIsOk(46, 70, 0.7));   // Temperature above range
    // Test cases for invalid SOC
    assert(!BatteryIsOk(25, 19, 0.7));   // SOC below range
    assert(!BatteryIsOk(25, 81, 0.7));   // SOC above range
    // Test cases for invalid charge rate
    assert(!BatteryIsOk(25, 70, 0.9));   // Charge rate above range
    // Test cases for invalid combinations
    assert(!BatteryIsOk(-1, 19, 0.9));   // Temperature and SOC below range
    assert(!BatteryIsOk(46, 81, 0.9));   // Temperature and SOC above range
    assert(!BatteryIsOk(25, 70, 1.0));   // Charge rate above range, within valid temperature and SOC
    // Test cases for edge values
    assert(!BatteryIsOk(0, 19, 0.7));    // Lower boundary for temperature, SOC below range
    assert(!BatteryIsOk(45, 81, 0.8));   // Upper boundary for temperature, SOC above range
    assert(BatteryIsOk(25, 70, 0.8));    // Valid at upper boundary of charge rate
    assert(BatteryIsOk(25, 70, 0.0));    // Valid at lower boundary of charge rate
}
