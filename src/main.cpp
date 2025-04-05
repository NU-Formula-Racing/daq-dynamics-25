#include <Arduino.h>
#include <Wire.h>
#include <MPU6050.h>
#include <vector>
#include "flow_rate.hpp"
#include "airspeed.hpp"
#include "thermistor.hpp"
#include "imu.hpp"
#include "define.h"

int currentTime;
int cloopTime; 

//Air Speed Object Setup
HWPin air_speed_pins[] = {AIR_SPEED_0, AIR_SPEED_1, AIR_SPEED_2, AIR_SPEED_3, AIR_SPEED_4, AIR_SPEED_5, AIR_SPEED_6, AIR_SPEED_7};
AirSpeed* air_speed_objects[7];
float air_speed_values[7];

// Flow Rate Objects
FlowRate flow_rate_object = FlowRate(FLOW_0);
FlowRate flow_rate_object = FlowRate(FLOW_1);

// Thermistor Objects
Thermistor thermistor_object = Thermistor(34, 35); 


IMU imu_object = IMU(); // subject to change 

void setup() 
{
   Serial.begin(9600);
    // Initializes each AirSpeed object with the corresponding pin, puts it in array
   for (int i = 0; i < 7; i++) 
   {
      air_speed_objects[i] = new AirSpeed(air_speed_pins[i]); // I feel like this shouldn't be dynamic.
   }
}

void loop() 
{
   imu_object.setup_IMU(); // has to use pins 21 and 22

   currentTime = millis();
   // // Every second, calculate and print litres/hour
   if(currentTime >= (cloopTime + 1000)) //changed from + 1000
   {
      cloopTime = currentTime; // Updates cloopTime
   }

   for (int i = 0; i < 7; i++) 
   {
      // Fills array with air_speed_values, can acts as a toggle to indicate which lights are on
      air_speed_values[i] = air_speed_objects[i]->readAirspeed();
   }
}