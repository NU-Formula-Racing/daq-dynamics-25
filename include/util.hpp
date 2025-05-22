#ifndef __UTIL_H__
#define __UTIL_H__

#include <Arduino.h>

#include "define.hpp"

class Util {
   public:
    static float readVoltage(HWPin pin) {
        float volts = 0;
        int adc = 0;
        long adc_sum = 0;  // must be long to hold a large value

        // read and accumulate the ADC value 10 times
        for (int i = 0; i < 10; i++) {
            adc = analogRead(pin);
            adc_sum = adc_sum + adc;
        }

        // divide by the number of readings to get the average
        adc = adc_sum / 10;

        // calculate the voltage using the averaged ADC
        if (adc > 3000) {
            volts = 0.0005 * adc + 1.0874;
        } else {
            volts = 0.0008 * adc + 0.1372;
        }
        // add any voltage scaling here
        volts = 3.3 * volts / 3.11;
        return volts;
    }

    static bool floatsEqual(float a, float b, float epsilon = 0.01) {
        return abs(a - b) <= epsilon;
    }
};

#endif  // __UTIL_H__