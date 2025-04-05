#pragma once
#include <Arduino.h>

class AirSpeed
{
private:
  const int _sensorPin;
  float _airspeed;
  const float _offset = .90; // Voltage at zero pressure 
  const float _scaleFactor = 1000; // Pressure per volt 
  const float _airDensity = 1.225; // Air density in kg/m^3 (standard at sea level)

public:
  bool _isActive; // Toggle to enable/disable airspeed reading
  // Creates a AirSpeed object who's input is read at "_sensorPin"
  AirSpeed(int pin) : _sensorPin(pin)
  {
    pinMode(_sensorPin, INPUT);
  };

  // calculates and returns airspeed
  float readAirspeed()
  {
    double _raw_voltage = analogRead(_sensorPin);
    double _voltage = (_raw_voltage / 4095.0) * 2.5;

    float _pressure = (_voltage - _offset) * _scaleFactor; // Differential pressure in Pa (Pascal)

    float airspeed = sqrt((2 * _pressure) / _airDensity); // Airspeed in meters/second
    return airspeed;
  }
};