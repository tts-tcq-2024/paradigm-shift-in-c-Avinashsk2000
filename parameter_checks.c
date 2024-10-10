#include <stdio.h>
#include "parameter_checks.h"
#include "warning_system.h"

int checkParameter(float value, float min, float max, const char* errorMessage, const char* lowWarning, const char* highWarning) {
    if (value < min || value > max) {
        printf("%s", errorMessage);
        return 0;
    }

    checkLowThreshold(value, min, max, lowWarning);
    checkHighThreshold(value, min, max, highWarning);

    return 1;
}
