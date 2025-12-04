// Define 485 communication pins 
#define RS485_RX_PIN 43
#define RS485_TX_PIN 44
// Redefine serial port name
#define RS485 Serial1
String strMsg = "";
void setup() {
  Serial.begin(115200);
  // Initialize 485 device
  pinMode(RS485_RX_PIN, INPUT_PULLUP);
  RS485.begin(115200, SERIAL_8N1, RS485_RX_PIN, RS485_TX_PIN);
  while (!RS485) {
    delay(10);  // Wait for initialization to succeed
  }
  RS485.print("TestRS485");
  RS485.flush();
}
void loop() {
  if (RS485.available()) {
    strMsg = RS485.readStringUntil('\r\n');
    RS485.print(strMsg);
    RS485.flush();
  }
}
