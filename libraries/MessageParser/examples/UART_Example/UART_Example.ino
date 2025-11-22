#include <MessageParser.h>
MessageParser parser;
/*
  String msg1 = "@03o131=3319,33";
  String msg2 = "@01o555?";
*/
String strMsg = "";
void setup() {
  Serial.begin(115200);
}
void loop() {
  if (Serial.available()) {
    strMsg = Serial.readString();
    Serial.flush();
    ParsedMessage p1 = parser.parse(strMsg);
    Serial.print("Message: ");
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
  }
}
