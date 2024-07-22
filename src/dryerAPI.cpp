//==============================================================
// Filename : dryerAPI.cpp
// Authors : Freek Bolding
// Description : Source file for API to dryer functionality
//==============================================================

#include "dryerAPI.h"

dryerAPI::dryerAPI(DHTesp* _dhtPtr, motor* _heaterPtr, motorPID* _pidPtr, motor* _fanPtr){
    dhtPtr = _dhtPtr;
    heaterPtr = _heaterPtr;
    pidPtr = _pidPtr;
    fanPtr = _fanPtr;
}

float dryerAPI::getHumidity(){
    return dhtPtr->getHumidity();
}

float dryerAPI::getTemperature(){
    return dhtPtr->getTemperature();
}

void dryerAPI::turnOnFan(){
    fanPtr->turnOn();
    fanPtr->setSpeed(255);
}

void dryerAPI::turnOffFan(){
    fanPtr->turnOff();
}

bool dryerAPI::isFanTurnedOn(){
    return fanPtr->getStatus();
}

void dryerAPI::setFanDutyCycle(float dutyCycle){
    fanPtr->turnOn();
    fanPtr->setSpeed(dutyCycle * 2.55); // Map (0,100) -> (0,255)
}
int dryerAPI::getFanDutyCycle(){
    return fanPtr->getSpeed() / 2.55; // Map (0,255) -> (0,100)
}

void dryerAPI::turnOnHeater(){
    heaterPtr->turnOn();
    pidPtr->stopControl = false;
}

void dryerAPI::turnOffHeater(){
    heaterPtr->turnOff();
    pidPtr->stopControl = true;
}

bool dryerAPI::isHeaterTurnedOn(){
    return heaterPtr->getStatus();
}

void dryerAPI::setTemperature(float temperature){
    pidPtr->setReference(temperature);
}

float dryerAPI::getReferenceTemperature(){
    return pidPtr->getReference();
}

int dryerAPI::getHeaterDutyCycle(){
    return heaterPtr->getSpeed() / 2.55; // Map (0,255) -> (0,100)
}

void dryerAPI::setPIDGains(float K_p, float K_i, float K_d){
    pidPtr->gain_P = K_p;
    pidPtr->gain_I = K_i;
    pidPtr->gain_D = K_d;
}
