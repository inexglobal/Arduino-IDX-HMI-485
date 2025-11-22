#include "MessageParser.h"

ParsedMessage MessageParser::parse(String msg) {
  ParsedMessage result;
  result.valueCount = 0;
  result.isQuery = false;

  msg.trim();

  int atPos = msg.indexOf('@');
  int oPos = msg.indexOf('o', atPos + 1);
  int eqPos = msg.indexOf('=');
  int qPos = msg.indexOf('?');

  if (atPos == -1 || oPos == -1) {
    Serial.println("❌ Invalid message format!");
    return result;
  }

  if (eqPos != -1) {
    result.header = msg.substring(atPos, oPos);
    result.command = msg.substring(oPos, eqPos);
  } else if (qPos != -1) {
    result.header = msg.substring(atPos, oPos);
    result.command = msg.substring(oPos, qPos);
    result.isQuery = true;
    return result;
  } else {
    Serial.println("❌ Invalid message (no '=' or '?')");
    return result;
  }

  // Parsing ค่า (value)
  String valueStr = msg.substring(eqPos + 1);
  int start = 0;
  int end = valueStr.indexOf(',');

  while (end != -1 && result.valueCount < 10) {
    result.values[result.valueCount++] = valueStr.substring(start, end);
    start = end + 1;
    end = valueStr.indexOf(',', start);
  }

  if (result.valueCount < 10 && start < valueStr.length()) {
    result.values[result.valueCount++] = valueStr.substring(start);
  }

  return result;
}
