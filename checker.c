#include <stdio.h>
#include <assert.h>

int checkAndPrint(float value, float min, float max, char message) {
    if (value < min || value > max) {
        printf("%s", message);
        return 0;
    }
    return 1;
}

int batteryIsOk(float temperature, float soc, float chargeRate) {
    int isTemperatureOk = checkAndPrint(temperature, 0, 45, "Temperature out of range!\n");
    int isSocOk = checkAndPrint(soc, 20, 80, "State of Charge out of range!\n");
    int isChargeRateOk = checkAndPrint(chargeRate, 0, 0.8, "Charge Rate out of range!\n");

    return isTemperatureOk && isSocOk && isChargeRateOk;
}

int main() {
    assert(batteryIsOk(25, 70, 0.7));    
    assert(!batteryIsOk(50, 85, 0));     
}
