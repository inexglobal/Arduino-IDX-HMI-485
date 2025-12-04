/*
    arm1.sendMsg("$H", OFF); // Homing
    arm1.sendMsg("~", OFF);  // Feed Hold
    arm1.sendMsg("!", OFF);  // Resume
    arm1.sendMsg("o111=vec2501", OFF); // run file "vec2501.gcode"
  */
#include <Mirobot.h>  //include header file
RS485_Mirobot arm1;
#define RS485_RX_PIN 4
#define RS485_TX_PIN 5
int pin_button_1 = 1;
int pin_button_2 = 6;

void setup() {
  Serial.begin(115200);
  arm1.rs485Init(01, 115200, RS485_RX_PIN, RS485_TX_PIN);
  arm1.setSerialMonitoring(1);
  pinMode(pin_button_1, INPUT);
  pinMode(pin_button_2, INPUT);
}
void loop() {
  if (digitalRead(pin_button_1) == 0) {
    arm1.sendMsg("$H", OFF);
    delay(250);
  }
  if (digitalRead(pin_button_1) == 0) {
    arm1.sendMsg("o111=vec2501", OFF);
    delay(250);
  }
}
