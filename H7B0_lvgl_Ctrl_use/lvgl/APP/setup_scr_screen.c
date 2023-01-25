/*
 * Copyright 2023 NXP
 * SPDX-License-Identifier: MIT
 * The auto-generated can only be used on NXP devices
 */

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "custom.h"


void setup_scr_screen(lv_ui *ui){

	//Write codes screen
	ui->screen = lv_obj_create(NULL);
	lv_obj_set_scrollbar_mode(ui->screen, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_main_main_default
	static lv_style_t style_screen_main_main_default;
	if (style_screen_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_main_main_default);
	else
		lv_style_init(&style_screen_main_main_default);
	lv_style_set_bg_color(&style_screen_main_main_default, lv_color_make(0xfd, 0x00, 0x6b));
	lv_style_set_bg_opa(&style_screen_main_main_default, 104);
	lv_obj_add_style(ui->screen, &style_screen_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_counter
	ui->screen_counter = lv_label_create(ui->screen);
	lv_obj_set_pos(ui->screen_counter, 509, 249);
	lv_obj_set_size(ui->screen_counter, 166, 88);
	lv_obj_set_scrollbar_mode(ui->screen_counter, LV_SCROLLBAR_MODE_AUTO);
	lv_label_set_text(ui->screen_counter, "0");
	lv_label_set_long_mode(ui->screen_counter, LV_LABEL_LONG_WRAP);

	//Write style state: LV_STATE_DEFAULT for style_screen_counter_main_main_default
	static lv_style_t style_screen_counter_main_main_default;
	if (style_screen_counter_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_counter_main_main_default);
	else
		lv_style_init(&style_screen_counter_main_main_default);
	lv_style_set_radius(&style_screen_counter_main_main_default, 0);
	lv_style_set_bg_color(&style_screen_counter_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_counter_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_counter_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_opa(&style_screen_counter_main_main_default, 0);
	lv_style_set_shadow_width(&style_screen_counter_main_main_default, 0);
	lv_style_set_shadow_color(&style_screen_counter_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_shadow_opa(&style_screen_counter_main_main_default, 255);
	lv_style_set_shadow_spread(&style_screen_counter_main_main_default, 0);
	lv_style_set_shadow_ofs_x(&style_screen_counter_main_main_default, 0);
	lv_style_set_shadow_ofs_y(&style_screen_counter_main_main_default, 0);
	lv_style_set_text_color(&style_screen_counter_main_main_default, lv_color_make(0x2F, 0x92, 0xDA));
	lv_style_set_text_font(&style_screen_counter_main_main_default, &lv_font_arial_80);
	lv_style_set_text_letter_space(&style_screen_counter_main_main_default, 2);
	lv_style_set_text_line_space(&style_screen_counter_main_main_default, 0);
	lv_style_set_text_align(&style_screen_counter_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_pad_left(&style_screen_counter_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_counter_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_counter_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_counter_main_main_default, 0);
	lv_obj_add_style(ui->screen_counter, &style_screen_counter_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_plus
	ui->screen_plus = lv_btn_create(ui->screen);
	lv_obj_set_pos(ui->screen_plus, 396, 372);
	lv_obj_set_size(ui->screen_plus, 166, 88);
	lv_obj_set_scrollbar_mode(ui->screen_plus, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_plus_main_main_default
	static lv_style_t style_screen_plus_main_main_default;
	if (style_screen_plus_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_plus_main_main_default);
	else
		lv_style_init(&style_screen_plus_main_main_default);
	lv_style_set_radius(&style_screen_plus_main_main_default, 50);
	lv_style_set_bg_color(&style_screen_plus_main_main_default, lv_color_make(0x75, 0xfd, 0x75));
	lv_style_set_bg_grad_color(&style_screen_plus_main_main_default, lv_color_make(0xed, 0x09, 0x09));
	lv_style_set_bg_grad_dir(&style_screen_plus_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_plus_main_main_default, 255);
	lv_style_set_shadow_width(&style_screen_plus_main_main_default, 0);
	lv_style_set_shadow_color(&style_screen_plus_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_shadow_opa(&style_screen_plus_main_main_default, 0);
	lv_style_set_shadow_spread(&style_screen_plus_main_main_default, 0);
	lv_style_set_shadow_ofs_x(&style_screen_plus_main_main_default, 0);
	lv_style_set_shadow_ofs_y(&style_screen_plus_main_main_default, 0);
	lv_style_set_border_color(&style_screen_plus_main_main_default, lv_color_make(0x6a, 0xbc, 0xc4));
	lv_style_set_border_width(&style_screen_plus_main_main_default, 5);
	lv_style_set_border_opa(&style_screen_plus_main_main_default, 255);
	lv_style_set_text_color(&style_screen_plus_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_plus_main_main_default, &lv_font_Alatsi_Regular_20);
	lv_style_set_text_align(&style_screen_plus_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_obj_add_style(ui->screen_plus, &style_screen_plus_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui->screen_plus_label = lv_label_create(ui->screen_plus);
	lv_label_set_text(ui->screen_plus_label, "Biu+");
	lv_obj_set_style_pad_all(ui->screen_plus, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->screen_plus_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes screen_minus
	ui->screen_minus = lv_btn_create(ui->screen);
	lv_obj_set_pos(ui->screen_minus, 623, 372);
	lv_obj_set_size(ui->screen_minus, 166, 88);
	lv_obj_set_scrollbar_mode(ui->screen_minus, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_minus_main_main_default
	static lv_style_t style_screen_minus_main_main_default;
	if (style_screen_minus_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_minus_main_main_default);
	else
		lv_style_init(&style_screen_minus_main_main_default);
	lv_style_set_radius(&style_screen_minus_main_main_default, 50);
	lv_style_set_bg_color(&style_screen_minus_main_main_default, lv_color_make(0x12, 0xe4, 0xb9));
	lv_style_set_bg_grad_color(&style_screen_minus_main_main_default, lv_color_make(0x4f, 0x12, 0xe4));
	lv_style_set_bg_grad_dir(&style_screen_minus_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_minus_main_main_default, 255);
	lv_style_set_shadow_width(&style_screen_minus_main_main_default, 0);
	lv_style_set_shadow_color(&style_screen_minus_main_main_default, lv_color_make(0x54, 0x5d, 0x96));
	lv_style_set_shadow_opa(&style_screen_minus_main_main_default, 219);
	lv_style_set_shadow_spread(&style_screen_minus_main_main_default, 0);
	lv_style_set_shadow_ofs_x(&style_screen_minus_main_main_default, 0);
	lv_style_set_shadow_ofs_y(&style_screen_minus_main_main_default, 0);
	lv_style_set_border_color(&style_screen_minus_main_main_default, lv_color_make(0x01, 0xa2, 0xb1));
	lv_style_set_border_width(&style_screen_minus_main_main_default, 4);
	lv_style_set_border_opa(&style_screen_minus_main_main_default, 255);
	lv_style_set_text_color(&style_screen_minus_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_font(&style_screen_minus_main_main_default, &lv_font_Alatsi_Regular_20);
	lv_style_set_text_align(&style_screen_minus_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_obj_add_style(ui->screen_minus, &style_screen_minus_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	ui->screen_minus_label = lv_label_create(ui->screen_minus);
	lv_label_set_text(ui->screen_minus_label, "Biu-");
	lv_obj_set_style_pad_all(ui->screen_minus, 0, LV_STATE_DEFAULT);
	lv_obj_align(ui->screen_minus_label, LV_ALIGN_CENTER, 0, 0);

	//Write codes screen_imgbtn_1
	ui->screen_imgbtn_1 = lv_imgbtn_create(ui->screen);
	lv_obj_set_pos(ui->screen_imgbtn_1, 0, 0);
	lv_obj_set_size(ui->screen_imgbtn_1, 377, 480);
	lv_obj_set_scrollbar_mode(ui->screen_imgbtn_1, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_imgbtn_1_main_main_default
	static lv_style_t style_screen_imgbtn_1_main_main_default;
	if (style_screen_imgbtn_1_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_imgbtn_1_main_main_default);
	else
		lv_style_init(&style_screen_imgbtn_1_main_main_default);
	lv_style_set_shadow_width(&style_screen_imgbtn_1_main_main_default, 0);
	lv_style_set_shadow_color(&style_screen_imgbtn_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_shadow_opa(&style_screen_imgbtn_1_main_main_default, 255);
	lv_style_set_shadow_spread(&style_screen_imgbtn_1_main_main_default, 0);
	lv_style_set_shadow_ofs_x(&style_screen_imgbtn_1_main_main_default, 0);
	lv_style_set_shadow_ofs_y(&style_screen_imgbtn_1_main_main_default, 0);
	lv_style_set_text_color(&style_screen_imgbtn_1_main_main_default, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_text_align(&style_screen_imgbtn_1_main_main_default, LV_TEXT_ALIGN_CENTER);
	lv_style_set_img_recolor(&style_screen_imgbtn_1_main_main_default, lv_color_make(0x0c, 0x0f, 0x0b));
	lv_style_set_img_recolor_opa(&style_screen_imgbtn_1_main_main_default, 0);
	lv_style_set_img_opa(&style_screen_imgbtn_1_main_main_default, 255);
	lv_obj_add_style(ui->screen_imgbtn_1, &style_screen_imgbtn_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_PRESSED for style_screen_imgbtn_1_main_main_pressed
	static lv_style_t style_screen_imgbtn_1_main_main_pressed;
	if (style_screen_imgbtn_1_main_main_pressed.prop_cnt > 1)
		lv_style_reset(&style_screen_imgbtn_1_main_main_pressed);
	else
		lv_style_init(&style_screen_imgbtn_1_main_main_pressed);
	lv_style_set_shadow_width(&style_screen_imgbtn_1_main_main_pressed, 0);
	lv_style_set_shadow_color(&style_screen_imgbtn_1_main_main_pressed, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_shadow_opa(&style_screen_imgbtn_1_main_main_pressed, 255);
	lv_style_set_shadow_spread(&style_screen_imgbtn_1_main_main_pressed, 0);
	lv_style_set_shadow_ofs_x(&style_screen_imgbtn_1_main_main_pressed, 0);
	lv_style_set_shadow_ofs_y(&style_screen_imgbtn_1_main_main_pressed, 0);
	lv_style_set_text_color(&style_screen_imgbtn_1_main_main_pressed, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_imgbtn_1_main_main_pressed, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_imgbtn_1_main_main_pressed, 0);
	lv_style_set_img_opa(&style_screen_imgbtn_1_main_main_pressed, 255);
	lv_obj_add_style(ui->screen_imgbtn_1, &style_screen_imgbtn_1_main_main_pressed, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style state: LV_STATE_CHECKED for style_screen_imgbtn_1_main_main_checked
	static lv_style_t style_screen_imgbtn_1_main_main_checked;
	if (style_screen_imgbtn_1_main_main_checked.prop_cnt > 1)
		lv_style_reset(&style_screen_imgbtn_1_main_main_checked);
	else
		lv_style_init(&style_screen_imgbtn_1_main_main_checked);
	lv_style_set_shadow_width(&style_screen_imgbtn_1_main_main_checked, 0);
	lv_style_set_shadow_color(&style_screen_imgbtn_1_main_main_checked, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_shadow_opa(&style_screen_imgbtn_1_main_main_checked, 255);
	lv_style_set_shadow_spread(&style_screen_imgbtn_1_main_main_checked, 0);
	lv_style_set_shadow_ofs_x(&style_screen_imgbtn_1_main_main_checked, 0);
	lv_style_set_shadow_ofs_y(&style_screen_imgbtn_1_main_main_checked, 0);
	lv_style_set_text_color(&style_screen_imgbtn_1_main_main_checked, lv_color_make(0xFF, 0x33, 0xFF));
	lv_style_set_img_recolor(&style_screen_imgbtn_1_main_main_checked, lv_color_make(0x00, 0x00, 0x00));
	lv_style_set_img_recolor_opa(&style_screen_imgbtn_1_main_main_checked, 0);
	lv_style_set_img_opa(&style_screen_imgbtn_1_main_main_checked, 255);
	lv_obj_add_style(ui->screen_imgbtn_1, &style_screen_imgbtn_1_main_main_checked, LV_PART_MAIN|LV_STATE_CHECKED);
	lv_imgbtn_set_src(ui->screen_imgbtn_1, LV_IMGBTN_STATE_RELEASED, NULL, &_darling_alpha_377x480, NULL);
	lv_imgbtn_set_src(ui->screen_imgbtn_1, LV_IMGBTN_STATE_CHECKED_RELEASED, NULL, &_preview_alpha_377x480, NULL);
	lv_obj_add_flag(ui->screen_imgbtn_1, LV_OBJ_FLAG_CHECKABLE);

	//Write codes screen_cpicker_1
	ui->screen_cpicker_1 = lv_colorwheel_create(ui->screen, true);
	lv_obj_set_pos(ui->screen_cpicker_1, 542, 68);
	lv_obj_set_size(ui->screen_cpicker_1, 100, 100);

	//Write style state: LV_STATE_DEFAULT for style_screen_cpicker_1_main_main_default
	static lv_style_t style_screen_cpicker_1_main_main_default;
	if (style_screen_cpicker_1_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_cpicker_1_main_main_default);
	else
		lv_style_init(&style_screen_cpicker_1_main_main_default);
	lv_style_set_arc_width(&style_screen_cpicker_1_main_main_default, 10);
	lv_obj_add_style(ui->screen_cpicker_1, &style_screen_cpicker_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_arc_1
	ui->screen_arc_1 = lv_arc_create(ui->screen);
	lv_obj_set_pos(ui->screen_arc_1, 409, 68);
	lv_obj_set_size(ui->screen_arc_1, 100, 100);
	lv_obj_set_scrollbar_mode(ui->screen_arc_1, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_arc_1_main_main_default
	static lv_style_t style_screen_arc_1_main_main_default;
	if (style_screen_arc_1_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_arc_1_main_main_default);
	else
		lv_style_init(&style_screen_arc_1_main_main_default);
	lv_style_set_radius(&style_screen_arc_1_main_main_default, 6);
	lv_style_set_bg_color(&style_screen_arc_1_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_arc_1_main_main_default, lv_color_make(0xf6, 0xf6, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_arc_1_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_arc_1_main_main_default, 255);
	lv_style_set_shadow_width(&style_screen_arc_1_main_main_default, 0);
	lv_style_set_shadow_color(&style_screen_arc_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_shadow_opa(&style_screen_arc_1_main_main_default, 255);
	lv_style_set_shadow_spread(&style_screen_arc_1_main_main_default, 0);
	lv_style_set_shadow_ofs_x(&style_screen_arc_1_main_main_default, 0);
	lv_style_set_shadow_ofs_y(&style_screen_arc_1_main_main_default, 0);
	lv_style_set_border_width(&style_screen_arc_1_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_arc_1_main_main_default, 20);
	lv_style_set_pad_right(&style_screen_arc_1_main_main_default, 20);
	lv_style_set_pad_top(&style_screen_arc_1_main_main_default, 20);
	lv_style_set_pad_bottom(&style_screen_arc_1_main_main_default, 20);
	lv_style_set_arc_color(&style_screen_arc_1_main_main_default, lv_color_make(0xe6, 0xe6, 0xe6));
	lv_style_set_arc_width(&style_screen_arc_1_main_main_default, 12);
	lv_obj_add_style(ui->screen_arc_1, &style_screen_arc_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_screen_arc_1_main_indicator_default
	static lv_style_t style_screen_arc_1_main_indicator_default;
	if (style_screen_arc_1_main_indicator_default.prop_cnt > 1)
		lv_style_reset(&style_screen_arc_1_main_indicator_default);
	else
		lv_style_init(&style_screen_arc_1_main_indicator_default);
	lv_style_set_arc_color(&style_screen_arc_1_main_indicator_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_arc_width(&style_screen_arc_1_main_indicator_default, 12);
	lv_obj_add_style(ui->screen_arc_1, &style_screen_arc_1_main_indicator_default, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_screen_arc_1_main_knob_default
	static lv_style_t style_screen_arc_1_main_knob_default;
	if (style_screen_arc_1_main_knob_default.prop_cnt > 1)
		lv_style_reset(&style_screen_arc_1_main_knob_default);
	else
		lv_style_init(&style_screen_arc_1_main_knob_default);
	lv_style_set_bg_color(&style_screen_arc_1_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_arc_1_main_knob_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_arc_1_main_knob_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_arc_1_main_knob_default, 255);
	lv_style_set_pad_all(&style_screen_arc_1_main_knob_default, 5);
	lv_obj_add_style(ui->screen_arc_1, &style_screen_arc_1_main_knob_default, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_arc_set_mode(ui->screen_arc_1, LV_ARC_MODE_NORMAL);
	lv_arc_set_range(ui->screen_arc_1, 0, 100);
	lv_arc_set_bg_angles(ui->screen_arc_1, 0, 360);
	lv_arc_set_angles(ui->screen_arc_1, 90, 180);
	lv_arc_set_rotation(ui->screen_arc_1, 0);
	lv_obj_set_style_arc_rounded(ui->screen_arc_1, 0,  LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_arc_rounded(ui->screen_arc_1, 0, LV_STATE_DEFAULT);

	//Write codes screen_roller_1
	ui->screen_roller_1 = lv_roller_create(ui->screen);
	lv_obj_set_pos(ui->screen_roller_1, 439, 200);
	lv_obj_set_scrollbar_mode(ui->screen_roller_1, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for style_screen_roller_1_main_main_default
	static lv_style_t style_screen_roller_1_main_main_default;
	if (style_screen_roller_1_main_main_default.prop_cnt > 1)
		lv_style_reset(&style_screen_roller_1_main_main_default);
	else
		lv_style_init(&style_screen_roller_1_main_main_default);
	lv_style_set_radius(&style_screen_roller_1_main_main_default, 5);
	lv_style_set_bg_color(&style_screen_roller_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_color(&style_screen_roller_1_main_main_default, lv_color_make(0xff, 0xff, 0xff));
	lv_style_set_bg_grad_dir(&style_screen_roller_1_main_main_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_roller_1_main_main_default, 255);
	lv_style_set_shadow_width(&style_screen_roller_1_main_main_default, 0);
	lv_style_set_shadow_color(&style_screen_roller_1_main_main_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_shadow_opa(&style_screen_roller_1_main_main_default, 255);
	lv_style_set_shadow_spread(&style_screen_roller_1_main_main_default, 0);
	lv_style_set_shadow_ofs_x(&style_screen_roller_1_main_main_default, 0);
	lv_style_set_shadow_ofs_y(&style_screen_roller_1_main_main_default, 0);
	lv_style_set_border_color(&style_screen_roller_1_main_main_default, lv_color_make(0xe6, 0xe6, 0xe6));
	lv_style_set_border_width(&style_screen_roller_1_main_main_default, 2);
	lv_style_set_border_opa(&style_screen_roller_1_main_main_default, 255);
	lv_style_set_text_color(&style_screen_roller_1_main_main_default, lv_color_make(0x33, 0x33, 0x33));
	lv_style_set_text_font(&style_screen_roller_1_main_main_default, &lv_font_montserratMedium_12);
	lv_obj_add_style(ui->screen_roller_1, &style_screen_roller_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for style_screen_roller_1_main_selected_default
	static lv_style_t style_screen_roller_1_main_selected_default;
	if (style_screen_roller_1_main_selected_default.prop_cnt > 1)
		lv_style_reset(&style_screen_roller_1_main_selected_default);
	else
		lv_style_init(&style_screen_roller_1_main_selected_default);
	lv_style_set_bg_color(&style_screen_roller_1_main_selected_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_color(&style_screen_roller_1_main_selected_default, lv_color_make(0x21, 0x95, 0xf6));
	lv_style_set_bg_grad_dir(&style_screen_roller_1_main_selected_default, LV_GRAD_DIR_NONE);
	lv_style_set_bg_opa(&style_screen_roller_1_main_selected_default, 255);
	lv_style_set_text_color(&style_screen_roller_1_main_selected_default, lv_color_make(0xFF, 0xFF, 0xFF));
	lv_style_set_text_font(&style_screen_roller_1_main_selected_default, &lv_font_montserratMedium_12);
	lv_obj_add_style(ui->screen_roller_1, &style_screen_roller_1_main_selected_default, LV_PART_SELECTED|LV_STATE_DEFAULT);
	lv_roller_set_options(ui->screen_roller_1,"1\n2\n3\n4\n5",LV_ROLLER_MODE_INFINITE);
	lv_roller_set_visible_row_count(ui->screen_roller_1,5);

	//Write codes screen_qrcode_1
	ui->screen_qrcode_1 = lv_qrcode_create(ui->screen, 100, lv_color_make(0x2C, 0x32, 0x24), lv_color_make(0xff, 0xff, 0xff));
	const char* screen_qrcode_1_data = "biubiu";
	lv_qrcode_update(ui->screen_qrcode_1, screen_qrcode_1_data, strlen(screen_qrcode_1_data));
	lv_obj_set_pos(ui->screen_qrcode_1, 675, 74);
	lv_obj_set_size(ui->screen_qrcode_1, 100, 100);

	//Init events for screen
	events_init_screen(ui);
}