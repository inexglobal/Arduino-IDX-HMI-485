#include <MessageParser.h>
// Define 485 communication pins
#define RS485_RX_PIN 43
#define RS485_TX_PIN 44
// Redefine serial port name
#define RS485 Serial1
String strMsg = "";
MessageParser parser;
void setup() {
  Serial.begin(115200);
  // Initialize 485 device
  pinMode(RS485_RX_PIN, INPUT_PULLUP);
  RS485.begin(115200, SERIAL_8N1, RS485_RX_PIN, RS485_TX_PIN);
  while (!RS485) {
    delay(10);  // Wait for initialization to succeed
  }
}
void loop() {
  if (RS485.available()) {
    strMsg = RS485.readString();
    RS485.flush();
    ParsedMessage p1 = parser.parse(strMsg);
    Serial.print("Message : ");
    Serial.println(strMsg);
    Serial.println("Header: " + p1.header);
    Serial.println("Command: " + p1.command);
    Serial.print("Is Query: ");
    Serial.println(p1.isQuery ? "true" : "false");
    for (int i = 0; i < p1.valueCount; i++) {
      Serial.print("Value ");
      Serial.print(i);
      Serial.print(": ");
      Serial.println(p1.values[i]);
    }
    RS485.println("ok");
  }
}