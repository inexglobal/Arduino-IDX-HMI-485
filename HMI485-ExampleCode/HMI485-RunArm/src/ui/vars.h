#ifndef EEZ_LVGL_UI_VARS_H
#define EEZ_LVGL_UI_VARS_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// enum declarations



// Flow global variables

enum FlowGlobalVariables {
    FLOW_GLOBAL_VARIABLE_NONE
};

// Native global variables

extern bool get_var_di0();
extern void set_var_di0(bool value);
extern bool get_var_di1();
extern void set_var_di1(bool value);
extern bool get_var_do0();
extern void set_var_do0(bool value);
extern bool get_var_do1();
extern void set_var_do1(bool value);
extern bool get_var_st_home();
extern void set_var_st_home(bool value);
extern bool get_var_st_start();
extern void set_var_st_start(bool value);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/