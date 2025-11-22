#ifndef MESSAGE_PARSER_H
#define MESSAGE_PARSER_H

#include <Arduino.h>

struct ParsedMessage {
  String header;      // เช่น @03
  String command;     // เช่น o131
  bool isQuery;       // true ถ้ามีเครื่องหมาย '?'
  String values[10];  // ถ้ามีค่า (3319, 33, ...)
  int valueCount;
};

class MessageParser {
public:
  MessageParser() {}
  ParsedMessage parse(String msg);
};

#endif
