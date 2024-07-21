//==============================================================
// Filename : tftUI.h
// Authors : Freek Bolding
// Description : Header file for simple control through TFT screen
//==============================================================

#ifndef TFTUI_H
#define TFTUI_H

// TFT pin definitions are located in lvconf.h

#include <lvgl.h>
#include <TFT_eSPI.h>
#include <ui.h>
#include "dryerAPI.h"
#include "timer.h"

// Forward declarations
void my_disp_flush( lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p );
void my_touchpad_read( lv_indev_drv_t * indev_driver, lv_indev_data_t * data );


class tftUI
{
    public:
        tftUI(dryerAPI* _dryerAPIPtr, const int _backlight_pin);
        void setup();
        void update();
    
    private:
        dryerAPI* dryerAPIPtr = nullptr; // Pointer to API 
        const int backlight_pin; // Backlight pin
        custom_timer timerUI{5}; // Call function every X ms


};

#endif