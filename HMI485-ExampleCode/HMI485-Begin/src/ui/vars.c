#include <stdio.h>
#include "vars.h"
#include <string.h>

bool sleep_mode = 1;

bool get_var_sleep_mode() {
    return sleep_mode;
}

void set_var_sleep_mode(bool value) {
    sleep_mode = value;
}

//-------------------------------------------------
bool do1;

bool get_var_do1() {
    return do1;
}

void set_var_do1(bool value) {
    do1 = value;
}
//--------------------------------------------------
bool do0;

bool get_var_do0() {
    return do0;
}

void set_var_do0(bool value) {
    do0 = value;
}
//-------------------------------------------------
bool di1;

bool get_var_di1() {
    return di1;
}

void set_var_di1(bool value) {
    di1 = value;
}
//-----------------------------------------
bool di0;

bool get_var_di0() {
    return di0;
}

void set_var_di0(bool value) {
    di0 = value;
}
//--------------------------------------------
