#include <Arduino.h>
const int analogPin = 32;
const float ADC_RESOLUTION = 4095.0;
const float REF_VOLTAGE = 3.3; 

// put function declarations here:

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(analogPin, INPUT);
  
}

void loop() {
  int adcValue = analogRead(analogPin);

  // Convert the ADC value to a voltage
  float voltage = (adcValue / ADC_RESOLUTION) * REF_VOLTAGE;
  //210 + -22.6 ln x
  float resistance =  (((REF_VOLTAGE/voltage)*1000)-1000);
  float temp = (210 - (22.6 * log(resistance)));
  
  Serial.print("Voltage at pin 32: ");
  Serial.print(voltage);
  Serial.println(" V");
  Serial.println(resistance);
  Serial.println(temp);
  delay(1000);
}

// put function definitions here: