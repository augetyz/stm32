/**
 * @file lv_demo_keypad_encoder.c
 *
 */

/*********************
 *      INCLUDES
 *********************/
#include "lv_demo_keypad_encoder.h"
#include "lvgl.h"
#if 1

static void selectors_create(lv_obj_t *parent);
static void text_input_create(lv_obj_t *parent);
static void msgbox_create(void);

static void msgbox_event_cb(lv_event_t *e);
static void ta_event_cb(lv_event_t *e);

static lv_group_t *g;
static lv_obj_t *tv;
static lv_obj_t *t1;
static lv_obj_t *t2;

void lv_demo_keypad_encoder(void)
{
     g = lv_group_create();
     lv_group_set_default(g);

     lv_indev_t *cur_drv = NULL;
     for (;;)
     {
          cur_drv = lv_indev_get_next(cur_drv);
          if (!cur_drv)
          {
               break;
          }

          if (cur_drv->driver->type == LV_INDEV_TYPE_KEYPAD)
          {
               lv_indev_set_group(cur_drv, g);
          }

          if (cur_drv->driver->type == LV_INDEV_TYPE_ENCODER)
          {
               lv_indev_set_group(cur_drv, g);
          }
     }

     tv = lv_tabview_create(lv_scr_act(), LV_DIR_TOP, LV_DPI_DEF / 3);

     t1 = lv_tabview_add_tab(tv, "Selectors");
     t2 = lv_tabview_add_tab(tv, "Text input");

     selectors_create(t1);
     text_input_create(t2);

     msgbox_create();
}
void lv_example_style_1(void)
{
    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_radius(&style, 5);

    /*Make a gradient*/
    lv_style_set_width(&style, 150);
    lv_style_set_height(&style, LV_SIZE_CONTENT);

    lv_style_set_pad_ver(&style, 20);
    lv_style_set_pad_left(&style, 5);

    lv_style_set_x(&style, lv_pct(50));
    lv_style_set_y(&style, 80);

    /*Create an object with the new style*/
    lv_obj_t * obj = lv_obj_create(lv_scr_act());
    lv_obj_add_style(obj, &style, 0);

    lv_obj_t * label = lv_label_create(obj);
    lv_label_set_text(label, "Hello");
}

void lv_example_span_1(void)
{
    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_border_width(&style, 1);
    lv_style_set_border_color(&style, lv_palette_main(LV_PALETTE_ORANGE));
    lv_style_set_pad_all(&style, 2);

    lv_obj_t * spans = lv_spangroup_create(lv_scr_act());
    lv_obj_set_width(spans, 300);
    lv_obj_set_height(spans, 300);
    lv_obj_center(spans);
    lv_obj_add_style(spans, &style, 0);

    lv_spangroup_set_align(spans, LV_TEXT_ALIGN_LEFT);
    lv_spangroup_set_overflow(spans, LV_SPAN_OVERFLOW_CLIP);
    lv_spangroup_set_indent(spans, 20);
    lv_spangroup_set_mode(spans, LV_SPAN_MODE_BREAK);

    lv_span_t * span = lv_spangroup_new_span(spans);
    lv_span_set_text(span, "China is a beautiful country.");
    lv_style_set_text_color(&span->style, lv_palette_main(LV_PALETTE_RED));
    lv_style_set_text_decor(&span->style, LV_TEXT_DECOR_UNDERLINE);
    lv_style_set_text_opa(&span->style, LV_OPA_50);

    span = lv_spangroup_new_span(spans);
    lv_span_set_text_static(span, "good good study, day day up.");
#if LV_FONT_MONTSERRAT_24
    lv_style_set_text_font(&span->style,  &lv_font_montserrat_24);
#endif
    lv_style_set_text_color(&span->style, lv_palette_main(LV_PALETTE_GREEN));

    span = lv_spangroup_new_span(spans);
    lv_span_set_text_static(span, "LVGL is an open-source graphics library.");
    lv_style_set_text_color(&span->style, lv_palette_main(LV_PALETTE_BLUE));

    span = lv_spangroup_new_span(spans);
    lv_span_set_text_static(span, "the boy no name.");
    lv_style_set_text_color(&span->style, lv_palette_main(LV_PALETTE_GREEN));
#if LV_FONT_MONTSERRAT_20
    lv_style_set_text_font(&span->style, &lv_font_montserrat_20);
#endif
    lv_style_set_text_decor(&span->style, LV_TEXT_DECOR_UNDERLINE);

    span = lv_spangroup_new_span(spans);
    lv_span_set_text(span, "I have a dream that hope to come true.");
    lv_style_set_text_decor(&span->style, LV_TEXT_DECOR_STRIKETHROUGH);

    lv_spangroup_refr_mode(spans);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

static void selectors_create(lv_obj_t *parent)
{
     lv_obj_set_flex_flow(parent, LV_FLEX_FLOW_COLUMN);
     lv_obj_set_flex_align(parent, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

     lv_obj_t *obj;

     obj = lv_table_create(parent);
     lv_table_set_cell_value(obj, 0, 0, "00");
     lv_table_set_cell_value(obj, 0, 1, "01");
     lv_table_set_cell_value(obj, 1, 0, "10");
     lv_table_set_cell_value(obj, 1, 1, "11");
     lv_table_set_cell_value(obj, 2, 0, "20");
     lv_table_set_cell_value(obj, 2, 1, "21");
     lv_table_set_cell_value(obj, 3, 0, "30");
     lv_table_set_cell_value(obj, 3, 1, "31");
     lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

     obj = lv_calendar_create(parent);
     lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

     obj = lv_btnmatrix_create(parent);
     lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

     obj = lv_checkbox_create(parent);
     lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

     obj = lv_slider_create(parent);
     lv_slider_set_range(obj, 0, 10);
     lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

     obj = lv_switch_create(parent);
     lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

     obj = lv_spinbox_create(parent);
     lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

     obj = lv_dropdown_create(parent);
     lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

     obj = lv_roller_create(parent);
     lv_obj_add_flag(obj, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

     lv_obj_t *list = lv_list_create(parent);
     lv_obj_update_layout(list);
     if (lv_obj_get_height(list) > lv_obj_get_content_height(parent))
     {
          lv_obj_set_height(list, lv_obj_get_content_height(parent));
     }

     lv_list_add_btn(list, LV_SYMBOL_OK, "Apply");
     lv_list_add_btn(list, LV_SYMBOL_CLOSE, "Close");
     lv_list_add_btn(list, LV_SYMBOL_EYE_OPEN, "Show");
     lv_list_add_btn(list, LV_SYMBOL_EYE_CLOSE, "Hide");
     lv_list_add_btn(list, LV_SYMBOL_TRASH, "Delete");
     lv_list_add_btn(list, LV_SYMBOL_COPY, "Copy");
     lv_list_add_btn(list, LV_SYMBOL_PASTE, "Paste");
}

static void text_input_create(lv_obj_t *parent)
{
     lv_obj_set_flex_flow(parent, LV_FLEX_FLOW_COLUMN);

     lv_obj_t *ta1 = lv_textarea_create(parent);
     lv_obj_set_width(ta1, LV_PCT(100));
     lv_textarea_set_one_line(ta1, true);
     lv_textarea_set_placeholder_text(ta1, "Click with an encoder to show a keyboard");

     lv_obj_t *ta2 = lv_textarea_create(parent);
     lv_obj_set_width(ta2, LV_PCT(100));
     lv_textarea_set_one_line(ta2, true);
     lv_textarea_set_placeholder_text(ta2, "Type something");

     lv_obj_t *kb = lv_keyboard_create(lv_scr_act());
     lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);

     lv_obj_add_event_cb(ta1, ta_event_cb, LV_EVENT_ALL, kb);
     lv_obj_add_event_cb(ta2, ta_event_cb, LV_EVENT_ALL, kb);
}

static void msgbox_create(void)
{
     static const char *btns[] = {"Ok", "Cancel", ""};
     lv_obj_t *mbox = lv_msgbox_create(NULL, "Hi", "Welcome to the keyboard and encoder demo", btns, false);
     lv_obj_add_event_cb(mbox, msgbox_event_cb, LV_EVENT_ALL, NULL);
     lv_group_focus_obj(lv_msgbox_get_btns(mbox));
     lv_obj_add_state(lv_msgbox_get_btns(mbox), LV_STATE_FOCUS_KEY);
#if LV_EX_MOUSEWHEEL
     lv_group_set_editing(g, true);
#endif
     lv_group_focus_freeze(g, true);

     lv_obj_align(mbox, LV_ALIGN_CENTER, 0, 0);

     lv_obj_t *bg = lv_obj_get_parent(mbox);
     lv_obj_set_style_bg_opa(bg, LV_OPA_70, 0);
     lv_obj_set_style_bg_color(bg, lv_palette_main(LV_PALETTE_GREY), 0);
}

static void msgbox_event_cb(lv_event_t *e)
{
     lv_event_code_t code = lv_event_get_code(e);
     lv_obj_t *msgbox = lv_event_get_current_target(e);

     if (code == LV_EVENT_VALUE_CHANGED)
     {
          const char *txt = lv_msgbox_get_active_btn_text(msgbox);
          if (txt)
          {
               lv_msgbox_close(msgbox);
               lv_group_focus_freeze(g, false);
               lv_group_focus_obj(lv_obj_get_child(t1, 0));
               lv_obj_scroll_to(t1, 0, 0, LV_ANIM_OFF);
          }
     }
}

static void ta_event_cb(lv_event_t *e)
{
     lv_indev_t *indev = lv_indev_get_act();
     if (indev == NULL)
          return;
     lv_indev_type_t indev_type = lv_indev_get_type(indev);

     lv_event_code_t code = lv_event_get_code(e);
     lv_obj_t *ta = lv_event_get_target(e);
     lv_obj_t *kb = lv_event_get_user_data(e);

     if (code == LV_EVENT_CLICKED && indev_type == LV_INDEV_TYPE_ENCODER)
     {
          lv_keyboard_set_textarea(kb, ta);
          lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
          lv_group_focus_obj(kb);
          lv_group_set_editing(lv_obj_get_group(kb), kb);
          lv_obj_set_height(tv, LV_VER_RES / 2);
          lv_obj_align(kb, LV_ALIGN_BOTTOM_MID, 0, 0);
     }

     if (code == LV_EVENT_READY || code == LV_EVENT_CANCEL)
     {
          lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
          lv_obj_set_height(tv, LV_VER_RES);
     }
}

#endif
