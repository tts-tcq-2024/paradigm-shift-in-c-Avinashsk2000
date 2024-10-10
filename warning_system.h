#ifndef WARNING_SYSTEM_H
#define WARNING_SYSTEM_H

extern float tolerance;  // 5% tolerance

void printWarningMessage(const char* message);
void checkLowThreshold(float value, float min, float max, const char* lowWarningMessage);
void checkHighThreshold(float value, float min, float max, const char* highWarningMessage);

#endif
