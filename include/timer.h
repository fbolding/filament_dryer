//==============================================================
// Filename : timer.h
// Authors : Freek Bolding
// Description : Very simple non-blocking timer class. hasElapsed()
//      should be called in loop in form of:
//      if (timerObject.hasElapsed()){
//          do stuff...
//      }
//==============================================================

#ifndef TIMER_H
#define TIMER_H
#include <Arduino.h>

class custom_timer
{
    public:
        custom_timer(): custom_timer(1000){}
        custom_timer(unsigned long _periodMS){
            setPeriod(_periodMS);
            hasElapsed();
        }
        void setPeriod(unsigned long _periodMS){period = _periodMS;}
        unsigned long getPeriod(){return period;}
        bool hasElapsed(){
            unsigned long currentTime = millis();
            if (currentTime - previousTime >= period){
                previousTime = currentTime;
                return true;
            } else {return false;}
        }

    private:
        unsigned long period = 1000;
        unsigned long previousTime = 0;
};
#endif