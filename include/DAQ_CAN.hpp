#include <CAN.h>


CAN can_bus{};

MakeSignedCANSignal(float, 0, 16, 1.0, 0.0) coolant_flow_rates_before_motor_flow_rate{};
MakeSignedCANSignal(float, 16, 16, 1.0, 0.0) coolant_flow_rates_before_accumulator_flow_rate{};

MakeSignedCANSignal(float, 32, 16, 1.0, 0.0) coolant_temps_before_motor_temperature{};
MakeSignedCANSignal(float, 48, 16, 1.0, 0.0) coolant_temps_before_accumulator_temperature{};

MakeSignedCANSignal(float, 0, 16, 1.0, 0.0) imu_acceleration_x{};
MakeSignedCANSignal(float, 16, 16, 1.0, 0.0) imu_acceleration_y{};
MakeSignedCANSignal(float, 32, 16, 1.0, 0.0) imu_acceleration_z{};

MakeSignedCANSignal(float, 0, 16, 1.0, 0.0) imu_gryo_x{};
MakeSignedCANSignal(float, 16, 16, 1.0, 0.0) imu_gryo_y{};
MakeSignedCANSignal(float, 32, 16, 1.0, 0.0) imu_gryo_z{};

MakeSignedCANSignal(float, 0, 16, 1.0, 0.0) lower_air_speed_0{};
MakeSignedCANSignal(float, 16, 16, 1.0, 0.0) lower_air_speed_1{};
MakeSignedCANSignal(float, 32, 16, 1.0, 0.0) lower_air_speed_2{};
MakeSignedCANSignal(float, 48, 16, 1.0, 0.0) lower_air_speed_3{};

MakeSignedCANSignal(float, 0, 16, 1.0, 0.0) upper_air_speed_4{};
MakeSignedCANSignal(float, 16, 16, 1.0, 0.0) upper_air_speed_5{};
MakeSignedCANSignal(float, 32, 16, 1.0, 0.0) upper_air_speed_6{};
MakeSignedCANSignal(float, 48, 16, 1.0, 0.0) upper_air_speed_7{};

CANTXMessage<2> DAQ_Coolant_Flow_Rates {can_bus, 0x134, 4, 0, coolant_flow_rates_before_motor_flow_rate, coolant_flow_rates_before_accumulator_flow_rate};
CANTXMessage<2> DAQ_Coolant_Temps {can_bus, 0x135, 8, 0, coolant_temps_before_motor_temperature, coolant_temps_before_accumulator_temperature};
CANTXMessage<3> DAQ_Dynamics_IMU_Acceleration {can_bus, 0x130, 6, 0, imu_acceleration_x, imu_acceleration_y, imu_acceleration_z};
CANTXMessage<3> DAQ_Dynamics_IMU_Gryo {can_bus, 0x131, 6, 0, imu_gryo_x, imu_gryo_y, imu_gryo_z};
CANTXMessage<4> DAQ_Dynamics_Pitot_Lower {can_bus, 0x132, 8, 0, lower_air_speed_0, lower_air_speed_1, lower_air_speed_2, lower_air_speed_3};
CANTXMessage<4> DAQ_Dynamics_Pitot_Upper{can_bus, 0x133, 8, 0, upper_air_speed_4, upper_air_speed_5, upper_air_speed_6, upper_air_speed_7};

void updateSignals(std::array<float, 8> airSpeed, std::array<float, 2> coolantTemperatures, std::array<float, 2> coolantFlowRate, std::array<float, 6> imu_data) {
   ///
   lower_air_speed_0 = airSpeed[0];
   lower_air_speed_1 = airSpeed[1];
   lower_air_speed_2 = airSpeed[2];
   lower_air_speed_3 = airSpeed[3];
   upper_air_speed_4 = airSpeed[4];
   upper_air_speed_5 = airSpeed[5];
   upper_air_speed_6 = airSpeed[6];
   upper_air_speed_7 = airSpeed[7];
   coolant_temps_before_motor_temperature = coolantTemperatures[0];
   coolant_temps_before_accumulator_temperature = coolantTemperatures[1];
   coolant_flow_rates_before_motor_flow_rate = coolantFlowRate[0];
   coolant_flow_rates_before_accumulator_flow_rate = coolantFlowRate[1];
   imu_acceleration_x = imu_data[0];
   imu_acceleration_y = imu_data[1];
   imu_acceleration_z = imu_data[2];
   imu_gryo_x = imu_data[3];
   imu_gryo_y = imu_data[4];
   imu_gryo_z = imu_data[5];

}