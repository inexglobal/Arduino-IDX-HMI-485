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
}
void loop() {
  if (RS485.available()) {
    strMsg = RS485.readString();
    RS485.flush();
    RS485.print(strMsg);
  }
}
