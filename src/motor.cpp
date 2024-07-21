//==============================================================
// Filename : motor.cpp
// Authors : Freek Bolding
// Description : Source file for motor functionality with L298N
//==============================================================

#include "motor.h"

motor::motor(const int IN1, const int IN2, const int ENA, const int pwm_channel):
    pin_in1(IN1), pin_in2(IN2), pin_ena(ENA), channel(pwm_channel){
        pinMode(pin_in1, OUTPUT);
        pinMode(pin_in2, OUTPUT);
        ledcSetup(channel, PWMFrequency, 8); // 8 Bits resolution
        ledcAttachPin(pin_ena, channel);
}

void motor::turnOn(){
    status = true;
    if (direction){ forward();}
    else { backward();}
}
void motor::turnOff(){
    status = false;
    digitalWrite(pin_in1, LOW);
    digitalWrite(pin_in2, LOW);
}

void motor::forward(){
    direction = true;
    Serial.print(F("Set direction to FORWARD"));
    digitalWrite(pin_in1, HIGH);
    digitalWrite(pin_in2, LOW);
}
void motor::backward(){
    direction = false;
    Serial.print(F("Set direction to BACKWARD"));
    digitalWrite(pin_in1, LOW);
    digitalWrite(pin_in2, HIGH);
}

void motor::setSpeed(const float& _speed){
    if (_speed < 0){ speed = 0;}
    else if (_speed > 255){ speed = 255;}
    else { speed = _speed;}
    Serial.print(F("Change PWM DutyCycle to "));
    Serial.println(speed);
    ledcWrite(channel, speed);
}
void motor::setSpeedPlus(const float& _speed){
    if (_speed == 0){ 
        turnOff(); // If speed is zero, turn off motor
        return; 
    } else if (!status){ status = true;} // Indicate motor is turned on

    if (_speed < 0){
        backward();
        setSpeed(-1 * _speed);
    }
    else {
        forward();
        setSpeed(_speed);
    }
}

void motor::setPWMFrequency(const float& _PWMFrequency){
    PWMFrequency = _PWMFrequency;
    Serial.print(F("Change PWM Frequency to "));
    Serial.println(PWMFrequency);
    ledcChangeFrequency(channel, PWMFrequency, 8);
}