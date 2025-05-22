#ifndef __AIRSPEED_H__
#define __AIRSPEED_H__

#include <Arduino.h>

#include "define.hpp"
#include "util.hpp"

class AirSpeed {
   public:
    bool _isActive = true;  // Toggle to enable/disable airspeed reading

    // Creates a AirSpeed object who's input is read at "_sensorPin"
    AirSpeed(HWPin pin) : _sensorPin(pin) {
        pinMode(_sensorPin, INPUT);
    };

    // calculates and returns airspeed
    float readAirspeed() {
        float pinVoltage = Util::readVoltage(_sensorPin);

        if (Util::floatsEqual(pinVoltage, 0)) {
            // this is being pulled down
            _isActive = false;
            return 0;
        }

        _isActive = true;
        // it is going through a voltage divider, where
        float sensorVoltage = pinVoltage / VOLTAGE_FACTOR;

        // now turn this into the pressure difference
        float pressureDifference = (((sensorVoltage - 0.1 * V_REF)) / ((0.8 * V_REF) / (P_MAX - P_MIN))) + P_MIN;

        float velSquared = (2.0 * pressureDifference) / AIR_DENSITY;

        return sqrt(abs(velSquared)) * (velSquared < 0) ? -1.0 : 1.0;
    }

    float getRawVoltage() {
        return Util::readVoltage(_sensorPin);
    }

    float getSensorVoltage() {
        float pinVoltage = Util::readVoltage(_sensorPin);
        float sensorVoltage = pinVoltage / VOLTAGE_FACTOR;
        return sensorVoltage;
    }

   private:
    const HWPin _sensorPin;
    const float P_MAX = 1.0;
    const float P_MIN = -1.0;
    const float V_REF = 3.3;

    const float VOLTAGE_DIV_R1 = 150;
    const float VOLTAGE_DIV_R2 = 9000;
    const float VOLTAGE_FACTOR = (VOLTAGE_DIV_R2 / (VOLTAGE_DIV_R2 + VOLTAGE_DIV_R1));

    const float AIR_DENSITY = 1.293;  // Air density in kg/m^3 (standard at sea level)
};
#endif  // __AIRSPEED_H__