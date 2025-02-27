#pragma once
#include <Arduino.h>

volatile int flow_frequency; // Measures flow sensor pulsesunsigned 

int l_min; // Calculated litres/min
const int flowsensor = GPIO_NUM_23; // Sensor Input
const int buttonPin = GPIO_NUM_22; // Button Input
double sum = 0.0;
int count = 0;

unsigned long currentTime;
unsigned long cloopTime;

void flow () // Interrupt function
{
   flow_frequency++;
}

void getFlowRate()
{
      l_min = (flow_frequency / 7.5 / 60 ); //flowrate in L/min
      flow_frequency = 0; // Resets Counter

      Serial.print(l_min, DEC); // Print litres/min
      Serial.println(" L/min");
}

   void setup()
 {
   pinMode(flowsensor, INPUT);
   digitalWrite(flowsensor, HIGH); // Optional Internal Pull-Up
   Serial.begin(9600);
   attachInterrupt(flowsensor, flow, RISING); // Setup Interrupt
   sei(); // Enable interrupts
   currentTime = millis();
   cloopTime = currentTime;
}

void loop ()
{
   // currentTime = millis();
   // // // Every second, calculate and print litres/hour
   // if(currentTime >= (cloopTime + 1000)) //changed from + 1000
   // {
   //    cloopTime = currentTime; // Updates cloopTime
   //    // Pulse frequency (Hz) = 7.5Q, Q is flow rate in L/min.
   //    getFlowRate();
   // }
}
