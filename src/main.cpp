#include <Arduino.h>
#include <Wire.h>
#include <MPU6050.h>
#include <vector>
#include "flow_rate.hpp"
#include "airspeed.hpp"
#include "thermistor.hpp"
#include "imu.hpp"
#include "define.h"
#include "DAQ_CAN.hpp"

int currentTime;
int cloopTime; 
float pot_resis = 1000;
//Just a Temporary Value, Should be changed based on the actual resistor used in hardware

//Air Speed Object Setup
HWPin air_speed_pins[] = {AIR_SPEED_0, AIR_SPEED_1, AIR_SPEED_2, AIR_SPEED_3, AIR_SPEED_4, AIR_SPEED_5, AIR_SPEED_6, AIR_SPEED_7};
AirSpeed* air_speed_objects[7];
float air_speed_values[7];

// Flow Rate Objects
FlowRate flow_rate_object_mot = FlowRate(FLOW_0);
FlowRate flow_rate_object_acc = FlowRate(FLOW_1);
float flow_rate_values[1];


// Thermistor Objects
Thermistor thermistor_object_mot = Thermistor(TEMP_0, pot_resis); 
Thermistor thermistor_object_acc = Thermistor(TEMP_1, pot_resis); 
float coolant_temperature_values[1];


IMU imu_object = IMU(); // subject to change 
float imu_values[5];


void setup() 
{
   Serial.begin(9600);
    // Initializes each AirSpeed object with the corresponding pin, puts it in array
   imu_object.setup_IMU(); // has to use pins 21 and 22
   for (int i = 0; i < 7; i++) 
   {
      air_speed_objects[i] = new AirSpeed(air_speed_pins[i]); // I feel like this shouldn't be dynamic.
   }
}

void loop() 
{
   
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

      // Fills array with temp_values
      coolant_temperature_values[0] = thermistor_object_mot.Read_Temp();
      coolant_temperature_values[1] = thermistor_object_acc.Read_Temp();
      // Fills array with flow_rate_values
      flow_rate_values[0] = flow_rate_object_mot.getFlowRate();
      flow_rate_values[1] = flow_rate_object_acc.getFlowRate();

   //TODO IMU Velocity and Position

   // package the values into arrays
   std::array<float, 8> Air_Speed_Vals = {air_speed_values[0], air_speed_values[1], air_speed_values[2], air_speed_values[3], air_speed_values[4], air_speed_values[5], air_speed_values[6], air_speed_values[7]};
   std::array<float, 2> Coolant_Temperature_Vals = {coolant_temperature_values[0], coolant_temperature_values[1]};
   std::array<float, 2> Flow_Rate_Vals = {flow_rate_values[0], flow_rate_values[1]};
   std::array<float, 6> IMU_Vals = imu_object.returnAccValues();
   updateSignals(Air_Speed_Vals, Coolant_Temperature_Vals, Flow_Rate_Vals, IMU_Vals);
   can_bus.Tick();

   
}