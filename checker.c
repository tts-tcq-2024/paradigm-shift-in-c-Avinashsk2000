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

// Function to check values and give early warnings
void checkWarning(float value, float min, float max, const char* warnLow, const char* warnHigh) {
    float lowerWarningLimit = min + tolerance * max;
    float upperWarningLimit = max - tolerance * max;

    // Arrays to hold the possible messages
    const char* warnings[] = {"", warnLow, warnHigh};

    // Determine which warning should be used (0 for none, 1 for low, 2 for high)
    int lowWarningIndex = (value > min && value <= lowerWarningLimit);  // Returns 1 if low warning, 0 otherwise
    int highWarningIndex = (value >= upperWarningLimit && value < max);  // Returns 1 if high warning, 0 otherwise

    // Use the appropriate index to select the warning (0 for none, 1 for low, 2 for high)
    const char* message = warnings[lowWarningIndex + 2 * highWarningIndex];

    // Print the selected message (if any)
    printf("%s", message);
}


// Function to check range and return error message if value exceeds limits
int checkAndWarn(float value, float min, float max, const char* errorMessage, const char* warnLow, const char* warnHigh) {
    if (value < min || value > max) {
        printf("%s", errorMessage);
        return 0;
    }

    checkWarning(value, min, max, warnLow, warnHigh); // Check warning levels
    return 1;
}

int batteryIsOk(float temperature, float soc, float chargeRate) {
    int isTemperatureOk = checkAndWarn(temperature, 0, 45, ERROR_TEMP, WARNING_TEMP_LOW, WARNING_TEMP_HIGH);
    int isSocOk = checkAndWarn(soc, 20, 80, ERROR_SOC, WARNING_SOC_LOW, WARNING_SOC_HIGH);
    int isChargeRateOk = checkAndWarn(chargeRate, 0, 0.8, ERROR_CHARGE, WARNING_CHARGE_LOW, WARNING_CHARGE_HIGH);

    return isTemperatureOk && isSocOk && isChargeRateOk;
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
}
