#include <Mirobot.h>  //include header file
//Create the robotic arm object
RS485_Mirobot HMI485;
void setup() {
  Serial.begin(115200);    //Initialize the serial port, the baud rate is 9600
  HMI485.rs485Init(99,115200);  //Initial setting, default address 01
}
void loop() {
  HMI485.sendMsg("$o131?", ON);
  String values[3];
  int count = HMI485.getResponse(',', values, 3);
  for (int i = 0; i < count; i++) {
    Serial.println(values[i]);
  }
}