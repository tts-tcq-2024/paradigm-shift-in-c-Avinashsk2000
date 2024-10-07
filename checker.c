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

// Function to print warning messages
void printWarning(const char* message) {
    if (message[0] != '\0') {  // Only print non-empty messages
        printf("%s", message);
    }
}

// Function to calculate warning limits
void calculateLimits(float min, float max, float *lowerWarningLimit, float *upperWarningLimit) {
    *lowerWarningLimit = min + (tolerance * max);
    *upperWarningLimit = max - (tolerance * max);
}

// Function to check and print temperature warnings
void checkTemperatureWarnings(float temperature, float min, float max) {
    float lowerWarningLimit, upperWarningLimit;
    calculateLimits(min, max, &lowerWarningLimit, &upperWarningLimit);

    printWarning((temperature > min && temperature <= lowerWarningLimit) ? WARNING_TEMP_LOW : "");
    printWarning((temperature >= upperWarningLimit && temperature < max) ? WARNING_TEMP_HIGH : "");
}

// Function to check temperature and print errors/warnings
void checkTemperature(float temperature) {
    float min = 0, max = 45;
    if (temperature < min || temperature > max) {
        printf("%s", ERROR_TEMP);
    } else {
        checkTemperatureWarnings(temperature, min, max);
    }
}

// Function to check and print SOC warnings
void checkSOCWarnings(float soc, float min, float max) {
    float lowerWarningLimit, upperWarningLimit;
    calculateLimits(min, max, &lowerWarningLimit, &upperWarningLimit);

    printWarning((soc > min && soc <= lowerWarningLimit) ? WARNING_SOC_LOW : "");
    printWarning((soc >= upperWarningLimit && soc < max) ? WARNING_SOC_HIGH : "");
}

// Function to check State of Charge (SoC) and print errors/warnings
void checkSOC(float soc) {
    float min = 20, max = 80;
    if (soc < min || soc > max) {
        printf("%s", ERROR_SOC);
    } else {
        checkSOCWarnings(soc, min, max);
    }
}

// Function to check and print charge rate warnings
void checkChargeRateWarnings(float chargeRate, float min, float max) {
    float lowerWarningLimit, upperWarningLimit;
    calculateLimits(min, max, &lowerWarningLimit, &upperWarningLimit);

    printWarning((chargeRate > min && chargeRate <= lowerWarningLimit) ? WARNING_CHARGE_LOW : "");
    printWarning((chargeRate >= upperWarningLimit && chargeRate < max) ? WARNING_CHARGE_HIGH : "");
}

// Function to check charge rate and print errors/warnings
void checkChargeRate(float chargeRate) {
    float min = 0, max = 0.8;
    if (chargeRate < min || chargeRate > max) {
        printf("%s", ERROR_CHARGE);
    } else {
        checkChargeRateWarnings(chargeRate, min, max);
    }
}

// Function to check battery status
int batteryIsOk(float temperature, float soc, float chargeRate) {
    checkTemperature(temperature);
    checkSOC(soc);
    checkChargeRate(chargeRate);

    // Return 1 only if all checks are okay
    return (temperature >= 0 && temperature <= 45) &&
           (soc >= 20 && soc <= 80) &&
           (chargeRate >= 0 && chargeRate <= 0.8);
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
