/*
 * Copyright 2023 NXP
 * SPDX-License-Identifier: MIT
 * The auto-generated can only be used on NXP devices
 */

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"
#include "guider_fonts.h"

typedef struct
{
	lv_obj_t *screen;
	bool screen_del;
	lv_obj_t *screen_counter;
	lv_obj_t *screen_plus;
	lv_obj_t *screen_plus_label;
	lv_obj_t *screen_minus;
	lv_obj_t *screen_minus_label;
	lv_obj_t *screen_imgbtn_1;
	lv_obj_t *screen_imgbtn_1_label;
	lv_obj_t *screen_cpicker_1;
	lv_obj_t *screen_arc_1;
	lv_obj_t *screen_roller_1;
	lv_obj_t *screen_qrcode_1;
}lv_ui;

void init_scr_del_flag(lv_ui *ui);
void setup_ui(lv_ui *ui);
extern lv_ui guider_ui;
void setup_scr_screen(lv_ui *ui);
LV_IMG_DECLARE(_preview_alpha_377x480);
LV_IMG_DECLARE(_darling_alpha_377x480);

#ifdef __cplusplus
}
#endif
#endif