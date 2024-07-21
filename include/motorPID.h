//==============================================================
// Filename : motorPID.h
// Authors : Freek Bolding
// Description : Header file controlling PWM duty cycle with PID
//==============================================================

#ifndef MOTORPID_H
#define MOTORPID_H

#include <Arduino.h>
#include <DHTesp.h>
#include "motor.h"
#include "timer.h"

class motorPID
{
    public:
        motorPID(motor* _plantPtr, DHTesp* _sensorPtr, float K_p, float K_i, float K_d);
        void update();

        void setReference(float _reference){ reference = _reference;};
        float getReference(){return reference;}
        void setControlLimit(float _min_value, float _max_value);

        float gain_P = 1;
        float gain_I = 0;
        float gain_D = 0;
        bool stopControl = false;
    private:
        float readSensor(){return sensorPtr->getTemperature();}
        void sendControl(float control);

        motor* plantPtr = nullptr;
        DHTesp* sensorPtr = nullptr;
        custom_timer control_timer{1}; // Control rule is updated every 1 ms

        float reference = 0;
        float current = 0;
        float error = 0;
        float error_derivative = 0;
        float error_integral = 0;

        float min_control = 0;
        float max_control = 100;
};
#endif