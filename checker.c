#include <stdio.h>
#include <assert.h>

int batteryIsOk(float temperature, float soc, float chargeRate) {
    int isTemperatureOk = (temperature >= 0 && temperature <= 45);
    int isSocOk = (soc >= 20 && soc <= 80);
    int isChargeRateOk = (chargeRate <= 0.8);

    if (!isTemperatureOk || !isSocOk || !isChargeRateOk) {
        if (!isTemperatureOk) {
            printf("Temperature out of range!\n");
        }
        if (!isSocOk) {
            printf("State of Charge out of range!\n");
        }
        if (!isChargeRateOk) {
            printf("Charge Rate out of range!\n");
        }
        return 0;
    }
    return 1;
}

int main() {
    assert(batteryIsOk(25, 70, 0.7) == 1);  // All values within range
    assert(batteryIsOk(-1, 70, 0.7) == 0);  // Temperature out of range
    assert(batteryIsOk(46, 70, 0.7) == 0);  // Temperature out of range
    assert(batteryIsOk(25, 19, 0.7) == 0);  // State of Charge out of range
    assert(batteryIsOk(25, 81, 0.7) == 0);  // State of Charge out of range
    assert(batteryIsOk(25, 70, 0.9) == 0);  // Charge Rate out of range
    assert(batteryIsOk(-1, 19, 0.9) == 0);  // Temperature out of range
    assert(batteryIsOk(50, 85, 1.0) == 0);  // Temperature out of range
    assert(batteryIsOk(0, 70, 0.7) == 1);   // Lower boundary
    assert(batteryIsOk(45, 70, 0.7) == 1);  // Upper boundary
    assert(batteryIsOk(25, 20, 0.7) == 1);  // Lower SOC boundary
    assert(batteryIsOk(25, 80, 0.7) == 1);  // Upper SOC boundary
    assert(batteryIsOk(25, 70, 0.8) == 1);  // Upper charge rate boundary
}
