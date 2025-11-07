#include <Arduino.h>
#include <esp_display_panel.hpp>
#include <lvgl.h>
#include <lvgl_v8_port.h>

/* include eez*/
#include <src/ui/ui.h>
#include <src/ui/vars.h>

using namespace esp_panel::drivers;
using namespace esp_panel::board;
#define DI0 0
#define DI1 5

#define DO0 8
#define DO1 9
esp_expander::CH422G *expander = NULL;
void setup() {
  Serial.begin(38400);
  Serial.println("Initializing board");

  Board *board = new Board();
  board->init();
  auto lcd = board->getLCD();
  lcd->configFrameBufferNumber(LVGL_PORT_DISP_BUFFER_NUM);
  auto lcd_bus = lcd->getBus();
  static_cast<BusRGB *>(lcd_bus)->configRGB_BounceBufferSize(lcd->getFrameWidth() * 10);
  assert(board->begin());
  Serial.println("Initializing LVGL");
  lvgl_port_init(board->getLCD(), board->getTouch());
  Serial.println("Creating UI");
  lvgl_port_lock(-1);
  ui_init();
  /* Release the mutex */
  lvgl_port_unlock();

  //Initialize IO expander
  expander = static_cast<esp_expander::CH422G *>(board->getIO_Expander()->getBase());
  expander->init();   // Initialize the expander
  expander->begin();  // Begin expander operation
  //"Set the OC pin to push-pull output mode
  expander->enableOC_PushPull();
  //Set the IO0-7 pin to input mode
  expander->enableAllIO_Input();

  
}
// Buffer สำหรับเก็บข้อความจาก Serial
String serialBuffer = "";
unsigned long t = 0;
void loop() {

  if (millis() - t >= 100) {  // เวลาครบรอบหน่วยเป็น มิลลิวินาที
    t = millis();
    ui_tick();  //update UI
  }

  bool var_st_home = get_var_st_home();
  bool var_st_start = get_var_st_start();
  if(var_st_home==1){
    Serial.println("RUN Home.....");
    set_var_st_home(0);
    set_var_st_start(0);
  }
   if(var_st_start==1){
    Serial.println("RUN Start.....");
    set_var_st_home(0);
    set_var_st_start(0);
  }
}