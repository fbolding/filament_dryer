//==============================================================
// Filename : dryerAPI.h
// Authors : Freek Bolding
// Description : Header file for API to dryer functionality
//==============================================================

#ifndef DRYERAPI_H
#define DRYERAPI_H

#include <Arduino.h>
#include <DHTesp.h>
#include "motor.h"
#include "motorPID.h"
class dryerAPI
{
    public:
        dryerAPI(DHTesp* _dhtPtr, motor* _heaterPtr, motorPID* _pidPtr, motor* _fanPtr);

        // DHT22 Sensor
        float getHumidity();
        float getTemperature();

        // Fan Control
        void turnOnFan();
        void turnOffFan();
        bool isFanTurnedOn();
        void setFanDutyCycle(float dutyCycle);
        int getFanDutyCycle();

        // Heat Control
        void turnOnHeater();
        void turnOffHeater();
        bool isHeaterTurnedOn();
        void setTemperature(float temperature);
        float getReferenceTemperature();
        int getHeaterDutyCycle();

        // PID gains
        void setPIDGains(float K_p, float K_i, float K_d);
        float getGainProportional() {return pidPtr->gain_P;}
        float getGainIntegral(){return pidPtr->gain_I;}
        float getGainDerivative(){return pidPtr->gain_D;}
    
    private:
        DHTesp* dhtPtr = nullptr;
        motor* heaterPtr = nullptr;
        motorPID* pidPtr = nullptr;
        motor* fanPtr = nullptr;
        int temporary;

};
#endif