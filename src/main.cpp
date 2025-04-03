#include <Arduino.h>
#include <Wire.h>
#include <MPU6050.h>
#include <vector>
#include "flow_rate.hpp"
#include "airspeed.hpp"
#include "thermistor.hpp"
#include "imu.hpp"

int currentTime;
int cloopTime; 

FlowRate flow_rate_object = FlowRate(23);
AirSpeed air_speed_object = AirSpeed(32);
Thermistor thermistor_object = Thermistor(34, 35); 
IMU imu_object = IMU(); // subject to change 

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
   imu_object.setup_IMU(); // has to use pins 21 and 22

   currentTime = millis();
   // // Every second, calculate and print litres/hour
   if(currentTime >= (cloopTime + 1000)) //changed from + 1000
   {
      cloopTime = currentTime; // Updates cloopTime
      // Pulse frequency (Hz) = 7.5Q, Q is flow rate in L/min.
      flow_rate_object.getFlowRate();
   }
}