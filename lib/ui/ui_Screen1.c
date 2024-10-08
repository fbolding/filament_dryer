// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.1
// LVGL version: 8.3.11
// Project name: filament_dryer

#include "ui.h"

void ui_Screen1_screen_init(void)
{
    ui_Screen1 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Screen1, lv_color_hex(0xDD9023), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_controlTemp = lv_arc_create(ui_Screen1);
    lv_obj_set_width(ui_controlTemp, 122);
    lv_obj_set_height(ui_controlTemp, 105);
    lv_obj_set_x(ui_controlTemp, -68);
    lv_obj_set_y(ui_controlTemp, 43);
    lv_obj_set_align(ui_controlTemp, LV_ALIGN_CENTER);
    lv_arc_set_value(ui_controlTemp, 50);


    ui_desiredTemp = lv_label_create(ui_controlTemp);
    lv_obj_set_width(ui_desiredTemp, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_desiredTemp, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_desiredTemp, -10);
    lv_obj_set_y(ui_desiredTemp, -3);
    lv_obj_set_align(ui_desiredTemp, LV_ALIGN_CENTER);
    lv_label_set_text(ui_desiredTemp, "desiredTemp");
    lv_obj_set_style_text_font(ui_desiredTemp, &lv_font_montserrat_14, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_controlFan = lv_arc_create(ui_Screen1);
    lv_obj_set_width(ui_controlFan, 122);
    lv_obj_set_height(ui_controlFan, 105);
    lv_obj_set_x(ui_controlFan, 84);
    lv_obj_set_y(ui_controlFan, 43);
    lv_obj_set_align(ui_controlFan, LV_ALIGN_CENTER);
    lv_arc_set_value(ui_controlFan, 50);


    ui_desiredFan = lv_label_create(ui_controlFan);
    lv_obj_set_width(ui_desiredFan, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_desiredFan, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_desiredFan, -10);
    lv_obj_set_y(ui_desiredFan, -3);
    lv_obj_set_align(ui_desiredFan, LV_ALIGN_CENTER);
    lv_label_set_text(ui_desiredFan, "desiredFan");

    ui_currentTemp = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_currentTemp, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_currentTemp, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_currentTemp, -77);
    lv_obj_set_y(ui_currentTemp, -71);
    lv_obj_set_align(ui_currentTemp, LV_ALIGN_CENTER);
    lv_label_set_text(ui_currentTemp, "currentTemp");

    ui_currentHumid = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_currentHumid, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_currentHumid, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_currentHumid, 71);
    lv_obj_set_y(ui_currentHumid, -63);
    lv_obj_set_align(ui_currentHumid, LV_ALIGN_CENTER);
    lv_label_set_text(ui_currentHumid, "currentHumid\n");

}
