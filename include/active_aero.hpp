#ifndef __ACTIVE_AERO__
#define __ACTIVE_AERO__
#include <Arduino.h>
#include <ESP32Servo.h>

class ActiveAero
{
public:
    enum class ActiveAeroPosition : uint16_t
    {
        kClosed = 1950,
        kOpen = 1400,
    };

    ActiveAero() {}

    void initialize()
    {
        ESP32PWM::allocateTimer(0);
        ESP32PWM::allocateTimer(1);
        ESP32PWM::allocateTimer(2);
        ESP32PWM::allocateTimer(3);
        _servo0.setPeriodHertz(50);
        _servo1.setPeriodHertz(50);
        _servo0.attach(HWPin::ACTIVE_AERO_0);
        _servo1.attach(HWPin::ACTIVE_AERO_1);
        _servo0.writeMicroseconds(static_cast<uint16_t>(ActiveAeroPosition::kClosed));
        _servo1.writeMicroseconds(static_cast<uint16_t>(ActiveAeroPosition::kClosed));
    }

    void commandPWM(bool activeAeroState)
    {
        uint16_t microseconds = activeAeroState ? static_cast<uint16_t>(ActiveAeroPosition::kOpen) : static_cast<uint16_t>(ActiveAeroPosition::kClosed);
        _servo0.writeMicroseconds(microseconds);
        _servo1.writeMicroseconds(microseconds);
    }

private:
    Servo _servo0;
    Servo _servo1;
};

#endif
