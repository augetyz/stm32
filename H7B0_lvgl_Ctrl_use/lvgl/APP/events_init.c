/*
 * Copyright 2023 NXP
 * SPDX-License-Identifier: MIT
 * The auto-generated can only be used on NXP devices
 */

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"
static unsigned int counter = 0;
static char buf[4];


void events_init(lv_ui *ui)
{
}

void video_play(lv_ui *ui)
{

}

static void screen_plus_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		counter++;
		sprintf(buf,  "%d" , counter);
		lv_label_set_text(guider_ui.screen_counter, buf);
		
	}
		break;
	default:
		break;
	}
}

static void screen_minus_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	switch (code)
	{
	case LV_EVENT_CLICKED:
	{
		if(counter) counter--;
		sprintf(buf,  "%d" , counter);
		lv_label_set_text(guider_ui.screen_counter, buf);
	}
		break;
	default:
		break;
	}
}

void events_init_screen(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->screen_plus, screen_plus_event_handler, LV_EVENT_ALL, ui);
	lv_obj_add_event_cb(ui->screen_minus, screen_minus_event_handler, LV_EVENT_ALL, ui);
}
