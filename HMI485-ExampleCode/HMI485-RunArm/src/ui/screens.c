#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;
lv_obj_t *tick_value_change_obj;

static void event_handler_cb_on_screen_on_screen(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_SCREEN_LOADED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 1, 0, e);
    }
}

static void event_handler_cb_monitor_obj0(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 4, 0, e);
    }
}

static void event_handler_cb_controll_obj1(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_CLICKED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 5, 0, e);
    }
}

static void event_handler_cb_controll_obj2(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_RELEASED) {
        e->user_data = (void *)0;
        flowPropagateValueLVGLEvent(flowState, 7, 0, e);
    }
}

static void event_handler_cb_controll_obj3(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    void *flowState = lv_event_get_user_data(e);
    (void)flowState;
    
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            assignBooleanProperty(flowState, 10, 3, value, "Failed to assign Checked state");
        }
    }
}

void create_screen_on_screen() {
    void *flowState = getFlowState(0, 0);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.on_screen = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    lv_obj_add_event_cb(obj, event_handler_cb_on_screen_on_screen, LV_EVENT_ALL, flowState);
    lv_obj_set_style_bg_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_img_create(parent_obj);
            lv_obj_set_pos(obj, 306, 145);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_img_set_src(obj, &img_logo);
        }
    }
    
    tick_screen_on_screen();
}

void tick_screen_on_screen() {
    void *flowState = getFlowState(0, 0);
    (void)flowState;
}

void create_screen_monitor() {
    void *flowState = getFlowState(0, 1);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.monitor = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 800, 108);
            add_style_tab_panel(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_imgbtn_create(parent_obj);
                    lv_obj_set_pos(obj, 11, 14);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, 81);
                    lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_RELEASED, NULL, &img_logo_sm, NULL);
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 118, 0);
                    lv_obj_set_size(obj, 157, 108);
                    add_style_active_tab(obj);
                    lv_obj_set_style_pad_top(obj, 35, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Monitor");
                }
                {
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.obj0 = obj;
                    lv_obj_set_pos(obj, 275, 0);
                    lv_obj_set_size(obj, 151, 108);
                    lv_obj_add_event_cb(obj, event_handler_cb_monitor_obj0, LV_EVENT_ALL, flowState);
                    add_style_inactive_tab(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.obj4 = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xff303030), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Controll");
                        }
                    }
                }
            }
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 215, 154);
            lv_obj_set_size(obj, 370, 293);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 11, 5);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Status Robot ARM");
                }
                {
                    lv_obj_t *obj = lv_led_create(parent_obj);
                    objects.obj5 = obj;
                    lv_obj_set_pos(obj, 189, 162);
                    lv_obj_set_size(obj, 51, 53);
                    lv_led_set_color(obj, lv_color_hex(0xffff9c00));
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 91, 171);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "RUN");
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 78, 89);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Home");
                }
                {
                    lv_obj_t *obj = lv_led_create(parent_obj);
                    objects.obj6 = obj;
                    lv_obj_set_pos(obj, 189, 80);
                    lv_obj_set_size(obj, 51, 53);
                    lv_led_set_color(obj, lv_color_hex(0xffff9c00));
                }
            }
        }
    }
    
    tick_screen_monitor();
}

void tick_screen_monitor() {
    void *flowState = getFlowState(0, 1);
    (void)flowState;
    {
        int32_t new_val = evalIntegerProperty(flowState, 8, 3, "Failed to evaluate Brightness in Led widget");
        if (new_val < 0) new_val = 0;
        else if (new_val > 255) new_val = 255;
        int32_t cur_val = lv_led_get_brightness(objects.obj5);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj5;
            lv_led_set_brightness(objects.obj5, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        int32_t new_val = evalIntegerProperty(flowState, 11, 3, "Failed to evaluate Brightness in Led widget");
        if (new_val < 0) new_val = 0;
        else if (new_val > 255) new_val = 255;
        int32_t cur_val = lv_led_get_brightness(objects.obj6);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj6;
            lv_led_set_brightness(objects.obj6, new_val);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_controll() {
    void *flowState = getFlowState(0, 2);
    (void)flowState;
    lv_obj_t *obj = lv_obj_create(0);
    objects.controll = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    {
        lv_obj_t *parent_obj = obj;
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 179, 213);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Home");
        }
        {
            lv_obj_t *obj = lv_obj_create(parent_obj);
            lv_obj_set_pos(obj, 0, 0);
            lv_obj_set_size(obj, 800, 108);
            add_style_tab_panel(obj);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_imgbtn_create(parent_obj);
                    lv_obj_set_pos(obj, 11, 14);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, 81);
                    lv_imgbtn_set_src(obj, LV_IMGBTN_STATE_RELEASED, NULL, &img_logo_sm, NULL);
                }
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 270, 0);
                    lv_obj_set_size(obj, 176, 108);
                    add_style_active_tab(obj);
                    lv_obj_set_style_pad_top(obj, 35, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Controll\n");
                }
                {
                    lv_obj_t *obj = lv_btn_create(parent_obj);
                    objects.obj1 = obj;
                    lv_obj_set_pos(obj, 119, 0);
                    lv_obj_set_size(obj, 151, 108);
                    lv_obj_add_event_cb(obj, event_handler_cb_controll_obj1, LV_EVENT_ALL, flowState);
                    add_style_inactive_tab(obj);
                    {
                        lv_obj_t *parent_obj = obj;
                        {
                            lv_obj_t *obj = lv_label_create(parent_obj);
                            objects.obj7 = obj;
                            lv_obj_set_pos(obj, 0, 0);
                            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                            lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_color(obj, lv_color_hex(0xff303030), LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_obj_set_style_text_font(obj, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
                            lv_label_set_text(obj, "Monitor");
                        }
                    }
                }
            }
        }
        {
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.obj2 = obj;
            lv_obj_set_pos(obj, 300, 306);
            lv_obj_set_size(obj, 130, 60);
            lv_obj_add_event_cb(obj, event_handler_cb_controll_obj2, LV_EVENT_ALL, flowState);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_22, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Start");
                }
            }
        }
        {
            lv_obj_t *obj = lv_label_create(parent_obj);
            lv_obj_set_pos(obj, 466, 213);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_32, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Run");
        }
        {
            lv_obj_t *obj = lv_switch_create(parent_obj);
            objects.obj3 = obj;
            lv_obj_set_pos(obj, 304, 199);
            lv_obj_set_size(obj, 126, 63);
            lv_obj_add_event_cb(obj, event_handler_cb_controll_obj3, LV_EVENT_ALL, flowState);
        }
        {
            // londing
            lv_obj_t *obj = lv_spinner_create(parent_obj, 1000, 60);
            objects.londing = obj;
            lv_obj_set_pos(obj, 275, 188);
            lv_obj_set_size(obj, 191, 178);
            lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
        }
    }
    
    tick_screen_controll();
}

void tick_screen_controll() {
    void *flowState = getFlowState(0, 2);
    (void)flowState;
    {
        bool new_val = evalBooleanProperty(flowState, 10, 3, "Failed to evaluate Checked state");
        bool cur_val = lv_obj_has_state(objects.obj3, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj3;
            if (new_val) lv_obj_add_state(objects.obj3, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj3, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
}


extern void add_style(lv_obj_t *obj, int32_t styleIndex);
extern void remove_style(lv_obj_t *obj, int32_t styleIndex);

static const char *screen_names[] = { "OnScreen", "Monitor", "Controll" };
static const char *object_names[] = { "on_screen", "monitor", "controll", "obj0", "obj1", "obj2", "obj3", "obj4", "obj5", "obj6", "obj7", "londing" };
static const char *style_names[] = { "active_tab", "inactive_tab", "tab_panel" };


typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_on_screen,
    tick_screen_monitor,
    tick_screen_controll,
};
void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen_funcs[screenId - 1]();
}

void create_screens() {
    eez_flow_init_styles(add_style, remove_style);
    
    eez_flow_init_screen_names(screen_names, sizeof(screen_names) / sizeof(const char *));
    eez_flow_init_object_names(object_names, sizeof(object_names) / sizeof(const char *));
    eez_flow_init_style_names(style_names, sizeof(style_names) / sizeof(const char *));
    
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_on_screen();
    create_screen_monitor();
    create_screen_controll();
}
