#ifndef __AIRSPEED_H__
#define __AIRSPEED_H__

#include <Arduino.h>

#include "define.h"

class AirSpeed {
   public:
    bool _isActive = true;  // Toggle to enable/disable airspeed reading

    // Creates a AirSpeed object who's input is read at "_sensorPin"
    AirSpeed(HWPin pin) : _sensorPin(pin) {
        pinMode(_sensorPin, INPUT);
    };

    // calculates and returns airspeed
    float readAirspeed() {
        double __adcCount = analogRead(_sensorPin);
        double _voltage = (__adcCount / 4095.0) * 2.5;

        float _pressure = (_voltage - _offset) * _scaleFactor;  // Differential pressure in Pa (Pascal)

        _airspeed = sqrt((2 * _pressure) / _airDensity);  // Airspeed in meters/second
        if (_airspeed == 0) {
            _offCount += 1;
        }

        if (_offCount >= 5) {
            _isActive = false;
            _offCount = 0;
        } else {
            _isActive = true;
        }
        return _airspeed;
    }

   private:
    const HWPin _sensorPin;
    const float _offset = .90;        // Voltage at zero pressure
    const float _scaleFactor = 1000;  // Pressure per volt
    const float _airDensity = 1.225;  // Air density in kg/m^3 (standard at sea level)
    float _airspeed;
    int _offCount = 0;
};
#endif  // __AIRSPEED_H__