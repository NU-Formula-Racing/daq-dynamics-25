#ifndef __DEFINE_H__
#define __DEFINE_H__

#include <Arduino.h>  // for gpio pins

// debug flags
#define DEBUG  // global debug flag
#define CAN_DEBUG

enum HWPin {

    // Airspeed Pins
    AIR_SPEED_6 = GPIO_NUM_14,
    AIR_SPEED_5 = GPIO_NUM_27,
    AIR_SPEED_1 = GPIO_NUM_32,
    AIR_SPEED_2 = GPIO_NUM_33,
    AIR_SPEED_7 = GPIO_NUM_34,
    AIR_SPEED_0 = GPIO_NUM_35,

    // NOTE: Not on Altium Schematic
    AIR_SPEED_3 = GPIO_NUM_36,
    AIR_SPEED_4 = GPIO_NUM_39,

    // Flowrate Pins
    FLOW_0 = GPIO_NUM_19,
    FLOW_1 = GPIO_NUM_23,

    // Active Aero Pins
    ACTIVE_AERO_0 = GPIO_NUM_25,
    ACTIVE_AERO_1 = GPIO_NUM_26,

    // Temperature Sensor Pins
    TEMP_0 = GPIO_NUM_12,
    TEMP_1 = GPIO_NUM_15,

    // CAN Pins
    DATA_CAN_RX = GPIO_NUM_4,
    STATUS_DATA = GPIO_NUM_16,
    STATUS_CLK = GPIO_NUM_17,
    DATA_CAN_TX = GPIO_NUM_5,

    // NOTE: Not on Altium Schematic
    ESP_RX = GPIO_NUM_3,
    ESP_TX = GPIO_NUM_1,

    // IMU Pins
    INT = GPIO_NUM_13,
    SDA = GPIO_NUM_21,
    SCL = GPIO_NUM_22,

};

#endif  // __DEFINE_H__