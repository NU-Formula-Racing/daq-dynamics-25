#ifndef __UTIL_H__
#define __UTIL_H__

#include <Arduino.h>

#include "define.hpp"

class Util {
   public:
    static float readVoltage(HWPin pin) {
        double reading = analogRead(pin);  // Reference voltage is 3v3 so maximum reading is 3v3 = 4095 in range 0 to 4095
        if (reading < 1 || reading > 4095) return 0;
        return -0.000000000000016 * pow(reading, 4) + 0.000000000118171 * pow(reading, 3) - 0.000000301211691 * pow(reading, 2) + 0.001109019271794 * reading + 0.034143524634089;
    }

    static bool floatsEqual(float a, float b, float epsilon = 0.01) {
        return abs(a - b) <= epsilon;
    }
};

#endif  // __UTIL_H__