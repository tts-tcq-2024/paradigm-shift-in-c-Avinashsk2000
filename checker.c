#include <stdio.h>
#include <assert.h>

#define ERROR_TEMP "Temperature out of range!\n"
#define ERROR_SOC "State of Charge out of range!\n"
#define ERROR_CHARGE "Charge Rate out of range!\n"
#define WARNING_TEMP "Warning: Approaching discharge or charge-peak!\n"
#define WARNING_SOC "Warning: Approaching discharge or charge-peak!\n"
#define WARNING_CHARGE "Warning: Approaching charge-peak!\n"

void printWarning(const char* message) {
    printf("%s", message);
}

int checkTemperatureWarning(float temperature) {
    float lowerLimit = 0.0;
    float upperLimit = 45.0;
    float tolerance = 0.05 * upperLimit; // 5% tolerance

    if (temperature < lowerLimit + tolerance || temperature > upperLimit - tolerance) {
        printWarning(WARNING_TEMP);
        return 1; // Warning triggered
    }
    return 0; // No warning
}

int checkSocWarning(float soc) {
    float lowerLimit = 20.0;
    float upperLimit = 80.0;
    float tolerance = 0.05 * upperLimit; // 5% tolerance

    if (soc < lowerLimit + tolerance || soc > upperLimit - tolerance) {
        printWarning(WARNING_SOC);
        return 1; // Warning triggered
    }
    return 0; // No warning
}

int checkChargeRateWarning(float chargeRate) {
    float upperLimit = 0.8;
    float tolerance = 0.05 * upperLimit; // 5% tolerance

    if (chargeRate > upperLimit - tolerance) {
        printWarning(WARNING_CHARGE);
        return 1; // Warning triggered
    }
    return 0; // No warning
}

int batteryIsOk(float temperature, float soc, float chargeRate) {
    int isTemperatureOk = (temperature >= 0 && temperature <= 45);
    int isSocOk = (soc >= 20 && soc <= 80);
    int isChargeRateOk = (chargeRate >= 0 && chargeRate <= 0.8);

    // Check for warnings
    checkTemperatureWarning(temperature);
    checkSocWarning(soc);
    checkChargeRateWarning(chargeRate);

    return isTemperatureOk && isSocOk && isChargeRateOk;
}

int main() {
    assert(batteryIsOk(25, 70, 0.7));
    assert(!batteryIsOk(50, 85, 0));
    // Test case for valid
    assert(batteryIsOk(0, 20, 0.0));     
    assert(batteryIsOk(45, 80, 0.8));    
    // Test cases for invalid temp
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
    // Test cases for edge values
    assert(!batteryIsOk(0, 19, 0.7)); 
    assert(!batteryIsOk(45, 81, 0.8));
    assert(batteryIsOk(25, 70, 0.8));    
    assert(batteryIsOk(25, 70, 0.0)); 
}
