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
  if (millis() - t >= 100) {  // เวลาครบรอบหน่วยเป็นมิลลิวินาที
     t = millis();
    bool var_do0 = get_var_do0();
    bool var_do1 = get_var_do1();
    
    expander->digitalWrite(DO0, !var_do0);
    expander->digitalWrite(DO1, !var_do1);
    bool var_di0 = expander->digitalRead(DI0);
    bool var_di1 = expander->digitalRead(DI1);

    set_var_di0(var_di0);
    set_var_di1(var_di1);
    set_var_do0(var_do0);
    set_var_do1(var_do1);
    ui_tick(); //update UI
  }
  
  

}