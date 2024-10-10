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
    assert(batteryIsOk(25, 70, 0.7));
    assert(batteryIsOk(0, 20, 0.0));     
    assert(batteryIsOk(45, 80, 0.8));
    assert(!batteryIsOk(-1, 70, 0.7));   
    assert(!batteryIsOk(46, 70, 0.7));   
    assert(!batteryIsOk(25, 19, 0.7));  
    assert(!batteryIsOk(25, 81, 0.7));  
    assert(!batteryIsOk(25, 70, 0.9));   

    return 0;
}
