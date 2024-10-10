#include <stdio.h>
#include <assert.h>
#include "parameter_checks.h"

int batteryIsOk(float temperature, float soc, float chargeRate) {
    int temperatureStatus = checkParameter(temperature, 0, 45, ERROR_TEMP, WARNING_TEMP_LOW, WARNING_TEMP_HIGH);
    int socStatus = checkParameter(soc, 20, 80, ERROR_SOC, WARNING_SOC_LOW, WARNING_SOC_HIGH);
    int chargeRateStatus = checkParameter(chargeRate, 0, 0.8, ERROR_CHARGE, WARNING_CHARGE_LOW, WARNING_CHARGE_HIGH);

    return temperatureStatus && socStatus && chargeRateStatus;
}

int main() {
    // Valid cases
    assert(batteryIsOk(25, 70, 0.7));   // Normal values within range
    assert(batteryIsOk(0, 20, 0.0));    // Lower edge of temperature and SOC
    assert(batteryIsOk(45, 80, 0.8));   // Upper edge of temperature, SOC, and charge rate

    // Test cases for invalid temperature
    assert(!batteryIsOk(-1, 70, 0.7));  // Below minimum temperature
    assert(!batteryIsOk(46, 70, 0.7));  // Above maximum temperature

    // Test cases for invalid SOC
    assert(!batteryIsOk(25, 19, 0.7));  // Below minimum SOC
    assert(!batteryIsOk(25, 81, 0.7));  // Above maximum SOC

    // Test cases for invalid charge rate
    assert(!batteryIsOk(25, 70, 0.9));  // Above maximum charge rate

    // Test cases for invalid combinations (multiple out of range)
    assert(!batteryIsOk(-1, 19, 0.9));  // Temperature, SOC, and charge rate all invalid
    assert(!batteryIsOk(46, 81, 0.9));  // Temperature, SOC, and charge rate all invalid
    assert(!batteryIsOk(25, 70, 1.0));  // Charge rate exceeds maximum

    // Edge cases
    assert(!batteryIsOk(0, 19, 0.7));   // Lower edge temperature, below minimum SOC
    assert(!batteryIsOk(45, 81, 0.8));  // Upper edge temperature, above maximum SOC
    assert(batteryIsOk(25, 70, 0.8));   // Upper charge rate at maximum
    assert(batteryIsOk(25, 70, 0.0));   // Minimum charge rate at 0

    // Test Temperature Warnings
    assert(batteryIsOk(1.0, 50, 0.5));  // Should trigger lower temperature warning
    assert(batteryIsOk(44.0, 50, 0.5)); // Should trigger upper temperature warning

    // Test SoC Warnings
    assert(batteryIsOk(25, 21.0, 0.5)); // Should trigger lower SOC warning
    assert(batteryIsOk(25, 79.0, 0.5)); // Should trigger upper SOC warning

    // Test Charge Rate Warnings
    assert(batteryIsOk(25, 50, 0.02));  // Should trigger lower charge rate warning
    assert(batteryIsOk(25, 50, 0.78));  // Should trigger upper charge rate warning

}
