#include "Mirobot.h"

class HardwareSerial;
HardwareSerial *serial;

UART_Mirobot::UART_Mirobot()
{
}

void UART_Mirobot::serialInit(int serialPort)
{
  commMode = 0;
  mirobotSerialPort = serialPort;
  switch (mirobotSerialPort)
  {
  case 0:
    serial = &Serial;
    break;
  case 1:
    serial = &Serial2;
    break;
  case 2:
    serial = &Serial2;
    break; // Note: case 2 also maps to Serial2
           // case 3: serial = &Serial3; break;
  default:
    serial = &Serial;
    break;
  }
  serial->begin(38400);
}

void UART_Mirobot::setSerialMonitoring(bool mode)
{
  serialMonitoringMode = mode;
}

void UART_Mirobot::homing(int homingMode)
{
  setCmdTimeout(30000);
  switch (homingMode)
  {
  case 1:
    sendMsg("$H1\nF2000");
    break;
  case 2:
    sendMsg("$H2\nF2000");
    break;
  case 3:
    sendMsg("$H3\nF2000");
    break;
  case 4:
    sendMsg("$H4\nF2000");
    break;
  case 5:
    sendMsg("$H5\nF2000");
    break;
  case 6:
    sendMsg("$H6\nF2000");
    break;
  case 7:
    sendMsg("$H7\nF2000");
    break;
  default:
    sendMsg("$H\nF2000");
    break;
  }
  setCmdTimeout(10000);
}

void UART_Mirobot::setMoveSpeed(int velocity)
{
  mirobotVelocity = velocity;
  sendMsg("F" + String(velocity));
}

void UART_Mirobot::setJumpPara(int height)
{
  String strCmd = "$49=" + String(height);
  sendMsg(strCmd);
}

void UART_Mirobot::timedPause(float seconds)
{
  String strCmd = "G04 P";
  String strPara = String(seconds, 3);
  sendMsg(strCmd + strPara);
}

void UART_Mirobot::zero()
{
  //  sendMsg("$M");
  sendMsg("M21 G90 G01 X0 Y0 Z0 A0 B0 C0");
}

void UART_Mirobot::moveJoints(float j1, float j2, float j3, float j4, float j5, float j6, bool motionMode)
{
  String strCmd = "M21 G00 ";
  if (motionMode)
    strCmd.concat("G90 ");
  else
    strCmd.concat("G91 ");
  String strParam = "X" + String(j1, 2) + " Y" + String(j2, 2) + " Z" + String(j3, 2) + " A" + String(j4, 2) + " B" + String(j5, 2) + " C" + String(j6, 2);
  strCmd.concat(strParam);
  sendMsg(strCmd);
}

void UART_Mirobot::movePose(float x, float y, float z, float rx, float ry, float rz, bool motionMode, int pathMode)
{
  String strCmd = "M20 ";
  switch (pathMode)
  {
  case MOVJ:
    strCmd.concat("G00 ");
    break;
  case MOVL:
    strCmd.concat("G01 ");
    break;
  case JUMP:
    strCmd.concat("G05 ");
    break;
  default:
    strCmd.concat("G00 ");
    break;
  }
  if (motionMode)
    strCmd.concat("G90 ");
  else
    strCmd.concat("G91 ");
  String strParam = "X" + String(x, 2) + " Y" + String(y, 2) + " Z" + String(z, 2) + " A" + String(rx, 2) + " B" + String(ry, 2) + " C" + String(rz, 2);
  strCmd.concat(strParam);
  sendMsg(strCmd);
}

void UART_Mirobot::moveArc(float x, float y, float z, float r, bool motionMode, int pathMode)
{
  String strCmd = "M20 ";
  if (motionMode)
    strCmd.concat("G90 ");
  else
    strCmd.concat("G91 ");
  if (pathMode)
    strCmd.concat("G02 ");
  else
    strCmd.concat("G03 ");
  String strParam = "X" + String(x, 2) + " Y" + String(y, 2) + " Z" + String(z, 2) + " R" + String(r, 2);
  strCmd.concat(strParam);
  sendMsg(strCmd);
}

void UART_Mirobot::gripper(int gripperStatus)
{
  if (gripperStatus)
    sendMsg("M3 S40");
  else
    sendMsg("M3 S60");
}

void UART_Mirobot::softGripper(int softGripperStatus)
{
  if (softGripperStatus == ON)
    sendMsg("M3 S1000");
  else if (softGripperStatus == GRAB)
    sendMsg("M3 S500");
  else
    sendMsg("M3 S0");
}

void UART_Mirobot::pump(int pumpStatus)
{
  if (pumpStatus == ON)
    sendMsg("M3 S1000");
  else if (pumpStatus == BLOW)
    sendMsg("M3 S500");
  else
    sendMsg("M3 S0");
}

void UART_Mirobot::pwmWrite(int pwm)
{
  String strPara = "S" + String(pwm);
  sendMsg("M3 " + strPara);
}

void UART_Mirobot::moveConveyor(float d, bool motionMode)
{
  sendMsg("$45=0");
  String strCmd = "G01 ";
  if (motionMode)
    strCmd.concat("G90 ");
  else
    strCmd.concat("G91 ");
  String strPara = "D " + String(d, 2);
  sendMsg(strCmd + strPara);
}

void UART_Mirobot::moveRail(float d, bool motionMode)
{
  sendMsg("$45=1");
  String strCmd = "G01 ";
  if (motionMode)
    strCmd.concat("G90 ");
  else
    strCmd.concat("G91 ");
  String strPara = "D " + String(d, 2);
  sendMsg(strCmd + strPara);
}

void UART_Mirobot::setCmdTimeout(long cmdTimeout)
{
  mirobotCmdTimeout = cmdTimeout;
}

void UART_Mirobot::sendMsg(String gcode, bool check)
{
  if (commMode == 0)
  {
    while (serial->read() >= 0)
    {
    };
    if (serial == reinterpret_cast<HardwareSerial *>(&Serial) || serialMonitoringMode == 0)
    {
      serial->println(gcode);
    }
    else
    {
      serial->println(gcode);
      Serial.println("Send message: " + gcode);
    }
    unsigned long rtime = millis();
    strMsg = "";
    while (strMsg.indexOf("ok") < 0 && strMsg.indexOf("State") < 0 && check && strMsg.length() != 2)
    {
      // If there is data in the serial port, read all of it
      // if(serial->available()) strMsg += serial->readString();
      if (serial->available())
        strMsg += serial->readStringUntil('/r/n'); // Note: This might be a typo for '\r' or '\n'
      // If waiting for the end character times out, break out
      if ((millis() - rtime) >= (mirobotCmdTimeout))
      {
        strMsg += "---Timeout---";
        break;
      }
      delay(100);
    }
    if (serial != reinterpret_cast<HardwareSerial *>(&Serial) && serialMonitoringMode == 1)
    {
      Serial.print("Mirobot: ");
      Serial.println(strMsg);
    }
  }
  else
  {
    String rs485Cmd = "@" + address + gcode;
    while (Serial2.read() >= 0)
    {
    };
    Serial2.println(rs485Cmd);
    Serial2.flush();
    delay(100);
    if (serialMonitoringMode == 1)
    {
      Serial.print("RS485 message: ");
      Serial.println(rs485Cmd);
    }
    unsigned long rtime = millis();
    strMsg = "";
    while (strMsg.indexOf("ok") < 0 && strMsg.indexOf("State") < 0 && check && strMsg.length() != 2)
    {
      // If there is data in the serial port, read all of it
      // if(Serial2.available()) strMsg = Serial2.readString();
      // if(Serial2.available()) strMsg = Serial2.readStringUntil('/r/n');
      while (Serial2.available())
      {
        char c = Serial2.read();
        // if (c == '\n') {
        // Serial.println(serialBuffer);
        // }else if (c != '\r') {
        if (c != '\r')
        {
          strMsg += c; // Store the character in the buffer
        }
      }
      // If waiting for the end character times out, break out
      if ((millis() - rtime) >= (mirobotCmdTimeout))
      {
        strMsg += "---Timeout---";
        break;
      }
      // delay(100);
    }
    if (serialMonitoringMode == 1)
    {
      Serial.print("Received: ");
      Serial.println(strMsg);
    }
  }
}

int UART_Mirobot::getStatus()
{
  sendMsg("O103");
  int Status;
  if (strMsg.indexOf("Offline") >= 0 || strMsg.indexOf("0") >= 0)
    Status = Offline;
  else if (strMsg.indexOf("Idle") >= 0 || strMsg.indexOf("1") >= 0)
    Status = Idle;
  else if (strMsg.indexOf("Alarm") >= 0 || strMsg.indexOf("2") >= 0)
    Status = Alarm;
  else if (strMsg.indexOf("Homing") >= 0 || strMsg.indexOf("3") >= 0)
    Status = Homing;
  else if (strMsg.indexOf("Run") >= 0 || strMsg.indexOf("5") >= 0)
    Status = Run;
  else if (strMsg.indexOf("Busy") >= 0 || strMsg.indexOf("4") >= 0)
    Status = Busy;
  else
    Status = Offline;
  return Status;
}

int UART_Mirobot::getResponse(char delimiter, String values[], int maxValues)
{
  String msg = strMsg;
  // msg.trim(); // Trim \r\n and spaces

  // Remove "ok" from the end if it exists
  if (msg.endsWith("ok"))
  {
    msg.remove(msg.length() - 2);
  }

  int start = 0;
  int end = msg.indexOf(delimiter);
  int count = 0;

  while (end != -1 && count < maxValues)
  {
    values[count++] = msg.substring(start, end);
    start = end + 1;
    end = msg.indexOf(delimiter, start);
  }

  // The last value
  if (start < msg.length() && count < maxValues)
  {
    values[count++] = msg.substring(start);
  }

  return count; // Return the number of values
}

void UART_Mirobot::runFile(String fileName)
{
  while (getStatus() != Idle && getStatus() != Alarm)
    ;
  String strCmd = "o111" + fileName;
  sendMsg(strCmd);
  delay(1000);
  while (getStatus() != Idle)
    ;
}

/*****************************************/

void RS485_Mirobot::rs485Init(int add, long baudRate, int RX_PIN, int TX_PIN)
{
  commMode = 1;
  address = String(add);
  if (address.length() < 2)
    address = "0" + address;
  pinMode(RX_PIN, INPUT_PULLUP);
  Serial2.begin(baudRate, SERIAL_8N1, RX_PIN, TX_PIN);
}