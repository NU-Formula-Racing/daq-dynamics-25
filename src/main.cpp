#include <Arduino.h>
#include <MPU6050.h>
#include <Wire.h>

#include <vector>

#include "can_interface.hpp"
#include "airspeed.hpp"
#include "define.hpp"
#include "flow_rate.hpp"
#include "imu.hpp"
#include "thermistor.hpp"

// Air Speed Object Setup
std::array<HWPin, 8> airSpeedPins = {AIR_SPEED_0, AIR_SPEED_1, AIR_SPEED_2, AIR_SPEED_3, AIR_SPEED_4, AIR_SPEED_5, AIR_SPEED_6, AIR_SPEED_7};
std::array<AirSpeed *, 8> airSpeedSensors;
std::array<float, 8> airSpeedValues;

// Flow Rate Objects
FlowRate motorCoolantFlowRate = FlowRate(FLOW_0);
FlowRate accumulatorCoolantFlowRate = FlowRate(FLOW_1);
std::array<float, 2> flowRateValues;

// Thermistor Objects
float potResist = 1000;
Thermistor motorCoolantTherm = Thermistor(TEMP_0, potResist);
Thermistor accumulatorCoolantTherm = Thermistor(TEMP_1, potResist);
std::array<float, 2> coolantTemperatureValues;

IMU imuObject = IMU();  // subject to change
std::array<float, 6> imuValues;

CANInterface can;

void setup() {
    Serial.begin(115200);
    Serial.println("Dynamics board start!");

    // imuObject.initialize();

    // Initializes each AirSpeed object with the corresponding pin, puts it in array
    for (int i = 0; i < 7; i++) {
        airSpeedSensors[i] = new AirSpeed(airSpeedPins[i]);  // I feel like this shouldn't be dynamic.
    }

    can.initialize();
}

void loop() {

    for (int i = 0; i < 7; i++) {
        // Fills array with air_speed_values, can acts as a toggle to indicate which lights are on
        airSpeedValues[i] = airSpeedSensors[i]->readAirspeed();
        Serial.printf("%0.2f m/s | ", airSpeedValues[i]);
    }

    // Fills array with temp_values
    coolantTemperatureValues[0] = motorCoolantTherm.readTemperature();
    coolantTemperatureValues[1] = accumulatorCoolantTherm.readTemperature();

    Serial.printf("%0.2f C | 0%.2f C | ", coolantTemperatureValues[0], coolantTemperatureValues[1]);

    // Fills array with flow_rate_values
    flowRateValues[0] = motorCoolantFlowRate.getFlowRate();
    flowRateValues[1] = accumulatorCoolantFlowRate.getFlowRate();

    Serial.printf("%0.2f C | 0%.2f C \n", flowRateValues[0], flowRateValues[1]);


    // imuValues = imuObject.getAccelValues();

    can.updateSignals(airSpeedValues, coolantTemperatureValues, flowRateValues, imuValues);

    delay(100);
}