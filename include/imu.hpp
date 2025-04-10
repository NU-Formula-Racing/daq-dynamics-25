#include <Arduino.h>
#include <Wire.h>
#include <MPU6050.h>
#include <vector>

class IMU
{
    MPU6050 __mpu;
    int16_t __ax, __ay, __az;
    int16_t __gx, __gy, __gz;
    float __AccX, __AccY, __AccZ, __GyroX, __GyroY, __GyroZ;
    float __pitchAcc, __rollAcc, __pitchGyro, __rollGyro, __yawGyro;
    float __velocityX = 0, __velocityY = 0, __velocityZ = 0;
    std::vector<double> __accelerationX = {0, 0};
    std::vector<double> __accelerationY = {0, 0};
    std::vector<double> __accelerationZ = {0, 0};
    std::vector<double> __velocityXVec = {0, 0};
    std::vector<double> __velocityYVec = {0, 0};
    std::vector<double> __velocityZVec = {0, 0};
    float __positionX = 0, __positionY = 0, __positionZ = 0;
    float __alpha = 0.2;
    float __pitch = 0, __roll = 0;

public:
    IMU() : __ax(0), __ay(0), __az(0), __gx(0), __gy(0), __gz(0),
            __AccX(0), __AccY(0), __AccZ(0), __GyroX(0), __GyroY(0), __GyroZ(0),
            __pitchAcc(0), __rollAcc(0), __pitchGyro(0), __rollGyro(0), __yawGyro(0),
            __velocityX(0), __velocityY(0), __velocityZ(0),
            __positionX(0), __positionY(0), __positionZ(0),
            __alpha(0.2), __pitch(0), __roll(0) {}

    std::vector<double> get_position()
    {
        std::vector<double> position = {__positionX, __positionY, __positionZ};
        return position;
    }

    void setup_IMU()
    {
        bool result = Wire.setPins(21, 22);
        if (result)
        {
            Serial.println("I2C pins successfully set!");
        }
        else
        {
            Serial.println("Failed to set I2C pins.");
            while (1)
                ; // Halt the program if the configuration fails
        }
        Wire.setClock(100000);
        Wire.begin();

        Serial.begin(9600);

        // Initialize the MPU6050 sensor
        Serial.println("Initializing MPU6050...");
        __mpu.initialize();

        // Check if MPU6050 is connected
        if (__mpu.testConnection())
        {
            Serial.println("MPU6050 is connected!");
        }
        else
        {
            Serial.println("MPU6050 connection failed!");
            while (1)
                ; // Halt the program if the sensor is not connected
        }
    }

    double integrate(const std::vector<double> &acceleration, double time_step)
    {
        if (acceleration.empty())
            return 0.0; // Handle empty input

        double velocity = 0.0;

        velocity += (acceleration[0] + acceleration[1]) * 0.5 * time_step;

        return velocity;
    }

    std::array<float, 6> returnAccValues()
    {
        __mpu.getMotion6(&__ax, &__ay, &__az, &__gx, &__gy, &__gz);
        __AccX = (float)__ax / 16384.0;
        __AccY = (float)__ay / 16384.0;
        __AccZ = (float)__az / 16384.0;
        __GyroX = (float)__gx / 131.0;
        __GyroY = (float)__gy / 131.0;
        __GyroZ = (float)__gz / 131.0;

        __accelerationX.push_back(__AccX);
        __accelerationY.push_back(__AccY);
        __accelerationZ.push_back(__AccZ);
        if (__accelerationX.size() > 2)
        {
            __accelerationX.erase(__accelerationX.begin());
            __accelerationY.erase(__accelerationY.begin());
            __accelerationZ.erase(__accelerationZ.begin());
        }

        std::array <float, 6> return_array = {__AccX, __AccY, __AccZ, __GyroX, __GyroY, __GyroZ};
        return return_array;
    }
    void calculate_pitch_roll()
    {
        __pitchAcc = atan2(__AccX, sqrt(__AccY * __AccY + __AccZ * __AccZ)) * 180 / PI;
        __rollAcc = atan2(__AccY, sqrt(__AccX * __AccX + __AccZ * __AccZ)) * 180 / PI;
    }
    void integrate_gyro(float dt)
    {
        __pitchGyro += __GyroY * dt;
        __rollGyro += __GyroX * dt;
    }
    void complementary_filter()
    {
        __pitch = __alpha * __pitchGyro + (1 - __alpha) * __pitchAcc;
        __roll = __alpha * __rollGyro + (1 - __alpha) * __rollAcc;
    }
    void remove_gravity()
    {
        __AccX -= 9.81 * sin(__pitch * PI / 180);
        __AccY += 9.81 * sin(__roll * PI / 180) * cos(__pitch * PI / 180);
        __AccZ += 9.81 * cos(__roll * PI / 180) * cos(__pitch * PI / 180);
    }
    void integrate_acceleration(float dt)
    {
        __velocityX = integrate(__accelerationX, dt);
        __velocityY = integrate(__accelerationY, dt);
        __velocityZ = integrate(__accelerationZ, dt);
    }
    void update_position(float dt)
    {
        __positionX += __velocityX * dt;
        __positionY += __velocityY * dt;
        __positionZ += __velocityZ * dt;
    }
    void print_position()
    {
        Serial.print("Position X: ");
        Serial.print(__positionX);
        Serial.print("\t");
        Serial.print("Position  Y: ");
        Serial.print(__positionY);
        Serial.print("\t");
        Serial.print("Position Z: ");
        Serial.print(__positionZ);
        Serial.println();
    }
    void delay_loop(unsigned long loopStartTime)
    {
        unsigned long loopTime = micros() - loopStartTime;
        if (loopTime < 10000)
        {
            delayMicroseconds(10000 - loopTime);
        }
    }
};
