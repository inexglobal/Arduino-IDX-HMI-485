#include <MessageParser.h>

MessageParser parser;

void setup() {
  Serial.begin(115200);
  delay(500);

  String msg1 = "@03o131=3319,33";
  String msg2 = "@01o555?";

  ParsedMessage p1 = parser.parse(msg1);
  ParsedMessage p2 = parser.parse(msg2);

  Serial.println("Message 1:");
  Serial.println("Header: " + p1.header);
  Serial.println("Command: " + p1.command);
  for (int i = 0; i < p1.valueCount; i++) {
    Serial.print("Value ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(p1.values[i]);
  }

  Serial.println("\nMessage 2:");
  Serial.println("Header: " + p2.header);
  Serial.println("Command: " + p2.command);
  Serial.print("Is Query: ");
  Serial.println(p2.isQuery ? "true" : "false");
}

void loop() {}
