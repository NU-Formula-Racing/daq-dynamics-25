#include <Arduino.h>
class Thermistor {
   private:
    int _analogPin;
    float ADC_RESOLUTION = 4095.0;
    float REF_VOLTAGE = 3.3;
    float _potResist;

   public:
    // Creates a Thermistor object who's input is read at "analogPin", and uses a resistor of "Pot_resis" ohms as the known resistor value
    Thermistor(int analogPin, float Pot_resis) : _analogPin(analogPin), _potResist(Pot_resis) {
        pinMode(analogPin, INPUT);
    };

    float readTemperature() {
        int adcValue = analogRead(_analogPin);
        // Convert the ADC value to a voltage
        float voltage = (adcValue / ADC_RESOLUTION) * REF_VOLTAGE;
        // 210 + -22.6 ln x
        float resistance = ((voltage * _potResist) / (REF_VOLTAGE - voltage));
        float temp = (210 - (22.6 * log(resistance)));
        return temp;
    }
    void Print_Setting() {
        Serial.print("Analog Pin: ");
        Serial.println(_analogPin);
        Serial.print("Potentiometer Resistance: ");
        Serial.println(_potResist);
    }
};