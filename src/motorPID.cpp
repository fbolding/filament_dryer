//==============================================================
// Filename : motorPID.cpp
// Authors : Freek Bolding
// Description : Source file for API to dryer functionality
//==============================================================

#include "motorPID.h"
#include <cmath>
motorPID::motorPID(motor* _plantPtr, DHTesp* _sensorPtr, float K_p, float K_i, float K_d){
    plantPtr = _plantPtr;
    sensorPtr = _sensorPtr;
    gain_P = K_p;
    gain_I = K_i;
    gain_D = K_d;
}

void motorPID::update(){
    unsigned long previousTime = control_timer.previousTime;
    if (!control_timer.hasElapsed() || stopControl){ return;}
    current = readSensor();

    unsigned long dt = control_timer.previousTime - previousTime;
    float previous_error = error;
    error = reference - current;
    error_derivative = (error-previous_error)/dt;
    error_integral += error*dt;
    control = gain_P*error + gain_D*error_derivative + gain_I*error_integral;
    
    // Limit control signal to min/max values
    if (control < min_control) {
        control = min_control;
        error_integral -= error*dt; // Anti wind-up
    } else if (control > max_control){
        control = max_control;
        error_integral -= error*dt; // Anti wind-up
    }
    sendControl(control);
}

float motorPID::readSensor(){
    float read = sensorPtr->getTemperature();
    if (isnan(read)){
        return current;
    }
    return read;
}

void motorPID::setControlLimit(float _min_value, float _max_value){
    min_control = _min_value;
    max_control = _max_value;
}

void motorPID::sendControl(float control){
    plantPtr->setSpeed(control * 2.55); // Motor takes values between 0-255, PID controls duty cycle between 0-100
}
