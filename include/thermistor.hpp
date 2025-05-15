#ifndef __THERMISTOR_H__
#define __THERMISTOR_H__

#include <Arduino.h>
#include "define.h"

class Thermistor {
   private:
   const float ADC_RESOLUTION = 4095.0;
   const float REF_VOLTAGE = 3.3;
   HWPin _analogPin;
   float _r2;

   public:
    // Creates a Thermistor object who's input is read at "analogPin", and uses a resistor of "Pot_resis" ohms as the known resistor value
    Thermistor(HWPin analogPin, float r2) : _analogPin(analogPin), _r2(r2) {
        pinMode(analogPin, INPUT);
    };

    float readTemperature() {
        int adcValue = analogRead(_analogPin);
        // Convert the ADC value to a voltage
        float voltage = (adcValue / ADC_RESOLUTION) * REF_VOLTAGE;
        // 210 + -22.6 ln x
        float resistance = ((voltage * _r2) / (REF_VOLTAGE - voltage));
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