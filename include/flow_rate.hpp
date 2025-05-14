#pragma once
#include <Arduino.h>

#include <functional>

#define MIN_CYCLE_TIME 500  // Test again

class FlowRate;

static void isr_flow(void *args);

class FlowRate {
   private:
    volatile unsigned long _flowCounter;  // Measures flow sensor pulsesunsigned
    float _lMin;                          // Calculated litres/min
    unsigned long _currentTime;
    unsigned long _loopTime;
    unsigned long _timeOfLastMeasurement;
    const int _sensorPin;  // Sensor Input

   public:
    void flow()  // Interrupt function
    {
        _flowCounter++;
    }

    // Creates a Flow Rate object who's input is read at "_sensorPin"
    FlowRate(int flowsensor) : _sensorPin(flowsensor), _timeOfLastMeasurement(0) {
        pinMode(flowsensor, INPUT);
        digitalWrite(flowsensor, HIGH);  // Optional Internal Pull-Up

        sei();  // Enable interrupts

        // attachInterruptArg(digitalPinToInterrupt(flowsensor), isr_flow, (void *)this, RISING);
    };

    float getFlowRate() {
        if (_timeOfLastMeasurement - millis() < MIN_CYCLE_TIME) {
            // we are measuring too early
            return _lMin;
        }

        // now we can actually measure it
        _timeOfLastMeasurement = millis();

        // number of turns ->
        // turns per second ->
        // liters per second ->
        // liters per minute ->
        unsigned long timeSinceLastMeasurement = _timeOfLastMeasurement - millis();

        double turnsPerSecond = (double)_flowCounter / (double)timeSinceLastMeasurement;

        _lMin = (turnsPerSecond / 7.5 / 60);  // flowrate in L/min
        _flowCounter = 0;                     // Resets Counter
        return _lMin;
    }
};

static void isr_flow(void *args) {
    FlowRate *sensor = (FlowRate *)args;
    sensor->flow();
}