#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

int batteryIsOk(float temperature, float soc, float chargeRate) {
    bool temperatureOk = temperature >= 0 && temperature <= 45;
    bool socOk = soc >= 20 && soc <= 80;
    bool chargeRateOk = chargeRate <= 0.8;
    
    if (temperatureOk && socOk && chargeRateOk) {
        return 1;
    } else {
        if (!temperatureOk) {
            printf("Temperature out of range!\n");
        } else if (!socOk) {
            printf("State of Charge out of range!\n");
        } else if (!chargeRateOk) {
            printf("Charge Rate out of range!\n");
        }
        return 0;
    }
}

int main() {
    assert(batteryIsOk(25, 70, 0.7));    
    assert(!batteryIsOk(50, 85, 0));     
}
