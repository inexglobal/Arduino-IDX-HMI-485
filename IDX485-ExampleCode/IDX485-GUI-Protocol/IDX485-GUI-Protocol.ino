#include <Mirobot.h>  //include header file
//Create the robotic arm object
RS485_Mirobot HMI485;
int32_t _count = 0;
int32_t _flag_reset = 0;
int32_t _flag_mode = 0;
void setup() {
  Serial.begin(115200);          //Initialize the serial port, the baud rate is 115200
  HMI485.rs485Init(99, 115200);  //Initial setting, default address 01
  HMI485.setSerialMonitoring(1); //Monitor setting, default 1:Open, 0:Off
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
}
void loop() {
  String msg = "";
  msg.concat(_count);
  HMI485.sendMsg("o131=" + msg, ON);
  String values[3];
  int count = HMI485.getResponse(',', values, 3);
  for (int i = 0; i < count; i++) {
    Serial.println(values[i]);
  }
  _flag_mode = values[0].toInt();
  _count = values[1].toInt() + 1;
  _flag_reset = values[2].toInt();
  digitalWrite(8,(_flag_mode ? 0:1 ));
  digitalWrite(9,(_flag_reset ? 0:1 ));
}