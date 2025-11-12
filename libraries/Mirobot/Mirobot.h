#ifndef _MIROBOT_H_
#define _MIROBOT_H_

#include <Arduino.h>

#define MOVJ 1
#define MOVL 2
#define JUMP 3

#define ABS 1
#define INC 0

#define CW 1
#define CCW 0

#define ON 1
#define OFF 0
#define GRAB 2
#define BLOW 2

#define Offline 0
#define Idle 1
#define Alarm 2
#define Homing 3
#define Run 5
#define Busy 4

class UART_Mirobot
{
public:
  UART_Mirobot();
  void serialInit(int serialPort = 0); // Set the serial port for communication with Mirobot (0/Serial; 1/Serial1; 2/Serial2; 3/Serial3)
  void setSerialMonitoring(bool mode); // Set to enable serial monitoring, view through Arduino serial monitor
  void setCmdTimeout(long cmdTimeout); // Set the timeout waiting time after each instruction is sent (unit: milliseconds ms)
  void homing(int homingMode = 0);     // Control the robotic arm homing (0/$H: quick homing; 1/$H1: axis 1 homing; 2/$H2: axis 2 homing; 3/$H3: axis 3 homing; 4/$H4: axis 4 homing;
                                   // 5/$H5: axis 5 homing; 6/$H6: axis 6 homing (requires corresponding hardware support); 7/$H7: rail homing;
  void zero();                     // Robotic arm initial position
  void setMoveSpeed(int velocity); // Set the robotic arm movement speed
  void setJumpPara(int height);    // Set the JUMP gate-shaped trajectory lift height
  void timedPause(float seconds);  // Pause/wait (unit: seconds s)

  void moveJoints(float j1, float j2, float j3, float j4, float j5, float j6, bool motionMode = ABS);                 // Angle mode movement
  void movePose(float x, float y, float z, float rx, float ry, float rz, bool motionMode = ABS, int pathMode = MOVJ); // Coordinate mode movement
  void moveArc(float x, float y, float z, float r, bool motionMode = ABS, int pathMode = CW);                         // Arc interpolation movement

  void gripper(int gripperStatus);         // Servo gripper status
  void softGripper(int softGripperStatus); // Three-finger soft gripper status
  void pump(int pumpStatus);               // Air pump status
  void pwmWrite(int pwm);                  // pwm (controller yellow interface) output, range: 0~1000

  void moveConveyor(float d, bool motionMode = ABS); // Conveyor belt movement control
  void moveRail(float d, bool motionMode = ABS);     // Slide rail movement control

  int getStatus(); // Get the robotic arm working status, 0/1/2/3/4/5: 0 robotic arm offline 1 normal 2 locked 3 resetting 4 device busy 5 running
  int getResponse(char delimiter, String values[], int maxValues);
  void runFile(String fileName); // Run the Gcode file stored in the controller
  void sendMsg(String gcode, bool check = ON);

protected:
  bool commMode;
  int mirobotSerialPort = 0;
  bool serialMonitoringMode = 1;
  int mirobotVelocity = 2000;
  long mirobotCmdTimeout = 10000L;
  void mirobotReceived();
  String strMsg = "";
  String address;
};

class RS485_Mirobot : public UART_Mirobot
{
public:
  void rs485Init(int add = 1, long baudRate = 38400, int RX_PIN = 4, int TX_PIN = 5);
};

#endif