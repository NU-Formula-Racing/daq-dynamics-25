#ifndef __THERMISTOR_H__
#define __THERMISTOR_H__

#include <Arduino.h>
#include "util.hpp"
#include "define.hpp"

class Thermistor {
   private:
   HWPin _analogPin;
   float _r2;
   const float REF_VOLTAGE = 3.3;

   public:
    // Creates a Thermistor object who's input is read at "analogPin", and uses a resistor of "Pot_resis" ohms as the known resistor value
    Thermistor(HWPin analogPin, float r2) : _analogPin(analogPin), _r2(r2) {
        pinMode(analogPin, INPUT);
    };

    float readTemperature() {
        float voltage = Util::readVoltage(_analogPin);
        // 210 + -22.6 ln x
        float resistance = (voltage * _r2) / (REF_VOLTAGE - voltage);
        float temp = (210 - (22.6 * log(resistance)));
        return temp;
    }

    void printSettings() {
        Serial.print("Analog Pin: ");
        Serial.println(_analogPin);
        Serial.print("Potentiometer Resistance: ");
        Serial.println(_r2);
    }
};
#endif // __THERMISTOR_H__