//==============================================================
// Filename : webUI.h
// Authors : Freek Bolding
// Description : Header file for simple control through web interface
//==============================================================

#ifndef WEBUI_H
#define WEBUI_H

#include <Arduino.h>
#include <EEPROM.h>
#include <ESPUI.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include "dryerAPI.h"



class webUI
{
    public:
        webUI(dryerAPI* _dryerAPIPtr);
        void setup();
        void update();
        
    private:
        dryerAPI* dryerAPIPtr = nullptr;

};
#endif