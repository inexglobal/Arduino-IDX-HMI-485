#include "MessageParser.h"

ParsedMessage MessageParser::parse(String msg) {
  ParsedMessage result;
  result.valueCount = 0;
  result.isQuery = false;

  // ---------------------
  // 1) แยก header (@xx)
  // ---------------------
  if (msg[0] == '@') {
    result.header = msg.substring(0, 3); 
    msg = msg.substring(3); 
  }

  // ---------------------
  // 2) ตัด checksum ถ้ามี ( *XX )
  // ---------------------
  int starIndex = msg.indexOf('*');
  if (starIndex != -1) {
    msg = msg.substring(0, starIndex);
  }

  // ---------------------
  // 3) เช็ค Query ?
  // ---------------------
  if (msg.endsWith("?")) {
    result.isQuery = true;
    msg.remove(msg.length() - 1);
  }

  // ---------------------
  // 4) แยกค่า =value,...
  // ---------------------
  int equalIndex = msg.indexOf('=');
  if (equalIndex != -1) {
    result.command = msg.substring(0, equalIndex);

    String valuesStr = msg.substring(equalIndex + 1);
    int start = 0;

    while (true) {
      int commaIndex = valuesStr.indexOf(',', start);
      if (commaIndex == -1) {
        result.values[result.valueCount++] = valuesStr.substring(start);
        break;
      }
      result.values[result.valueCount++] = valuesStr.substring(start, commaIndex);
      start = commaIndex + 1;
    }

  } else {
    result.command = msg;
  }

  return result;
}
