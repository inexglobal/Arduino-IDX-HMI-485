#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *on_screen;
    lv_obj_t *monitor;
    lv_obj_t *controll;
    lv_obj_t *obj0;
    lv_obj_t *obj1;
    lv_obj_t *obj2;
    lv_obj_t *obj3;
    lv_obj_t *obj4;
    lv_obj_t *obj5;
    lv_obj_t *obj6;
    lv_obj_t *obj7;
    lv_obj_t *obj8;
    lv_obj_t *obj9;
    lv_obj_t *obj10;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_ON_SCREEN = 1,
    SCREEN_ID_MONITOR = 2,
    SCREEN_ID_CONTROLL = 3,
};

void create_screen_on_screen();
void tick_screen_on_screen();

void create_screen_monitor();
void tick_screen_monitor();

void create_screen_controll();
void tick_screen_controll();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/