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

#include <MessageParser.h>

// Define 485 communication pins
#define RS485_RX_PIN 43
#define RS485_TX_PIN 44
// Redefine serial port name
#define RS485 Serial1
String strMsg = "";
MessageParser parser;

void setup() {
  Serial.begin(38400);
  Serial.println("Initializing board");

  pinMode(RS485_RX_PIN, INPUT_PULLUP);
  RS485.begin(115200, SERIAL_8N1, RS485_RX_PIN, RS485_TX_PIN);
  while (!RS485) {
    delay(10);  // Wait for initialization to succeed
  }

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
unsigned long t = 0;
int32_t _count = 0;
int32_t _flag_reset = 0;
int32_t _flag_mode = 0;
void loop() {

  _flag_reset = get_var_flag_reset();
  _flag_mode = get_var_flag_mode();

  if (millis() - t >= 100) {  // เวลาครบรอบหน่วยเป็นมิลลิวินาที
    t = millis();
    ui_tick();  //update UI
  }
  if (RS485.available()) {
    strMsg = RS485.readString();
    RS485.flush();
    ParsedMessage p1 = parser.parse(strMsg);
    if (p1.header == "@99") {
      if (p1.command == "o131") {
        if (p1.valueCount > 0) {
          _count = p1.values[0].toInt();
          set_var_count(_count);
        }
        String msg = "";
        msg.concat(_flag_mode);
        msg.concat(",");
        msg.concat(_count);
        msg.concat(",");
        msg.concat(_flag_reset);
        RS485.println(msg + "ok");
      }
    }
  }
}
