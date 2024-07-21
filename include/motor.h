//==============================================================
// Filename : motor.h
// Authors : Freek Bolding
// Description : Header file for motor functionality with L298N
//==============================================================

#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

class motor
{
    public:
        motor(const int IN1, const int IN2, const int ENA, const int pwm_channel);
        void turnOn();
        void turnOff();
        bool getStatus(){ return status;};

        void forward();
        void backward();
        bool getDirection(){ return direction;};

        void setSpeed(const float& _speed); // Takes value between 0 - 255
        void setSpeedPlus(const float& _speed); // Takes value between -255 - 255
        float getSpeed(){ return speed;};
        
        void setPWMFrequency(const float& _PWMfrequency);
        float getPWMFrequency(){ return PWMFrequency;};
        

    private:
        const int pin_in1;
        const int pin_in2;
        const int pin_ena;
        const int channel;
        bool status = false; // True if turned on, False if turned off
        bool direction = true; // True if forward, False if backward
        float speed = 0; // Actually duty cycle of PWM, 0 for off and 100 for full speed
        float PWMFrequency = 20000;

};
#endif