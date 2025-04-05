#include <CAN.h>


CAN can_bus{};

MakeSignedCANSignal(float, 0, 16, 1.0, 0.0) coolant_flow_rates_before_motor_flow_rate{};
MakeSignedCANSignal(float, 16, 16, 1.0, 0.0) coolant_flow_rates_before_accumulator_flow_rate{};

MakeSignedCANSignal(float, 32, 16, 1.0, 0.0) coolant_temps_before_motor_temperature{};
MakeSignedCANSignal(float, 48, 16, 1.0, 0.0) coolant_temps_before_accumulator_temperature{};

MakeSignedCANSignal(float, 0, 16, 1.0, 0.0) imu_acceleration_x_acceleration{};
MakeSignedCANSignal(float, 16, 16, 1.0, 0.0) imu_acceleration_y_acceleration{};
MakeSignedCANSignal(float, 32, 16, 1.0, 0.0) imu_acceleration_z_acceleration{};

MakeSignedCANSignal(float, 0, 16, 1.0, 0.0) imu_gryo_x_angular_speed{};
MakeSignedCANSignal(float, 16, 16, 1.0, 0.0) imu_gryo_y_angular_speed{};
MakeSignedCANSignal(float, 32, 16, 1.0, 0.0) imu_gryo_z_angular_speed{};

MakeSignedCANSignal(float, 0, 16, 1.0, 0.0) lower_air_speed_0{};
MakeSignedCANSignal(float, 16, 16, 1.0, 0.0) lower_air_speed_1{};
MakeSignedCANSignal(float, 32, 16, 1.0, 0.0) lower_air_speed_2{};
MakeSignedCANSignal(float, 48, 16, 1.0, 0.0) lower_air_speed_3{};

MakeSignedCANSignal(float, 0, 16, 1.0, 0.0) upper_air_speed_4{};
MakeSignedCANSignal(float, 16, 16, 1.0, 0.0) upper_air_speed_5{};
MakeSignedCANSignal(float, 32, 16, 1.0, 0.0) upper_air_speed_6{};
MakeSignedCANSignal(float, 48, 16, 1.0, 0.0) upper_air_speed_7{};

void can_transmit()
{
   CANTXMessage<2> DAQ_Coolant_Flow_Rates {can_bus, 0x134, 4, 0, coolant_flow_rates_before_motor_flow_rate, coolant_flow_rates_before_accumulator_flow_rate};
   CANTXMessage<2> DAQ_Coolant_Temps {can_bus, 0x135, 8, 0, coolant_temps_before_motor_temperature, coolant_temps_before_accumulator_temperature};
   CANTXMessage<3> DAQ_Dynamics_IMU_Acceleration {can_bus, 0x130, 6, 0, imu_acceleration_x_acceleration, imu_acceleration_y_acceleration, imu_acceleration_z_acceleration};
   CANTXMessage<3> DAQ_Dynamics_IMU_Gryo {can_bus, 0x131, 6, 0, imu_gryo_x_angular_speed, imu_gryo_y_angular_speed, imu_gryo_z_angular_speed};
   CANTXMessage<4> DAQ_Dynamics_Pitot_Lower {can_bus, 0x132, 8, 0, lower_air_speed_0, lower_air_speed_1, lower_air_speed_2, lower_air_speed_3};
   CANTXMessage<4> DAQ_Dynamics_Pitot_Upper{can_bus, 0x133, 8, 0, upper_air_speed_4, upper_air_speed_5, upper_air_speed_6, upper_air_speed_7};
}