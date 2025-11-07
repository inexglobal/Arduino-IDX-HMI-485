#include "actions.h"
#include "ui.h"

void action_on_changed(lv_event_t *e) {
    ui_tick();
}
