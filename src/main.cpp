//==============================================================
// Filename : main.cpp
// Authors : Freek Bolding
// Description : Main file for filament dryer.
//==============================================================

// ------------- INCLUDE HEADERS -------------
#include <Arduino.h>
#include <WiFi.h>
#include "DHTesp.h"
#include "motor.h"
#include "dryerAPI.h"
#include "tftUI.h"
#include "webUI.h"
#include "timer.h"

// ------------- PIN DEFINITIONS -------------
// DHT22
const int DHT_IN = 6;

// Heater
const int HEAT_IN1 = 3;
const int HEAT_IN2 = 5;
const int HEAT_EN = 16;

// Fan
const int FAN_IN1 = 2;
const int FAN_IN2 = 4;
const int FAN_EN = 7;

// TFT Screen (most pins defined in lv_conf.h)
const int TFT_BL = 15;

// ------------- GLOBAL VARIABLES -------------
DHTesp dht;
motor heater(HEAT_IN1, HEAT_IN2, HEAT_EN, 4);
motorPID tempControl(&heater, &dht, 14, 0, 0); // Calculate I gain with DC[%]/error[degC] * 1/time[s]
motor fan(FAN_IN1, FAN_IN2, FAN_EN, 5);
dryerAPI api(&dht, &heater, &tempControl, &fan);
tftUI tftInterface(&api, TFT_BL);
webUI webInterface(&api);

custom_timer serial_timer(1000);
custom_timer fan_timer(5000);

void setup(){
    Serial.begin( 115200 );
    Serial.println("Starting in 5 sec");
    delay(5000);
    dht.setup(DHT_IN, DHTesp::DHT22);
    tftInterface.setup();
    webInterface.setup();
}

void loop(){
    tempControl.update();
    tftInterface.update();
    webInterface.update();
    if (serial_timer.hasElapsed()){
        Serial.println(dht.getTemperature());
        Serial.println(tempControl.getReference());
        Serial.println(tempControl.getControl());
    }
}

