#include <Arduino.h>
#include <MPU6050.h>
#include <Wire.h>

#include <vector>

#include "DAQ_CAN.hpp"
#include "airspeed.hpp"
#include "define.h"
#include "flow_rate.hpp"
#include "imu.hpp"
#include "thermistor.hpp"

int currentTime;
int cloopTime;
float pot_resis = 1000;
// Just a Temporary Value, Should be changed based on the actual resistor used in hardware

// Air Speed Object Setup
HWPin airSpeedPins[] = {AIR_SPEED_0, AIR_SPEED_1, AIR_SPEED_2, AIR_SPEED_3, AIR_SPEED_4, AIR_SPEED_5, AIR_SPEED_6, AIR_SPEED_7};
AirSpeed* airSpeedSensors[7];
std::array<float, 8> airSpeedValues;

// Flow Rate Objects
FlowRate motorCoolantFlowRate = FlowRate(FLOW_0);
FlowRate accumulatorCoolantFlowRate = FlowRate(FLOW_1);
std::array<float, 2> flowRateValues;

// Thermistor Objects
Thermistor motorCoolantTherm = Thermistor(TEMP_0, pot_resis);
Thermistor accumulatorCoolantTherm = Thermistor(TEMP_1, pot_resis);
std::array<float, 2> coolantTemperatureValues;

IMU imuObject = IMU();  // subject to change
std::array<float, 6> imuValues;

void setup() {
    Serial.begin(115200);
    // Initializes each AirSpeed object with the corresponding pin, puts it in array
    imuObject.initialize();  // has to use pins 21 and 22
    for (int i = 0; i < 7; i++) {
        airSpeedSensors[i] = new AirSpeed(airSpeedPins[i]);  // I feel like this shouldn't be dynamic.
    }
}

void loop() {
    currentTime = millis();
    // // Every second, calculate and print litres/hour
    if (currentTime >= (cloopTime + 1000)) {
        cloopTime = currentTime;  // Updates cloopTime
    }

    for (int i = 0; i < 7; i++) {
        // Fills array with air_speed_values, can acts as a toggle to indicate which lights are on
        airSpeedValues[i] = airSpeedSensors[i]->readAirspeed();
    }

    // Fills array with temp_values
    coolantTemperatureValues[0] = motorCoolantTherm.readTemperature();
    coolantTemperatureValues[1] = accumulatorCoolantTherm.readTemperature();
    // Fills array with flow_rate_values
    flowRateValues[0] = motorCoolantFlowRate.getFlowRate();
    flowRateValues[1] = accumulatorCoolantFlowRate.getFlowRate();

    imuValues = imuObject.returnAccValues();
    
    updateSignals(airSpeedValues, coolantTemperatureValues, flowRateValues, imuValues);
    can_bus.Tick();
}