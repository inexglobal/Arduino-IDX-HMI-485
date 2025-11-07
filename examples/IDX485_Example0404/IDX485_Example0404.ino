void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 255; i+=5) {
    analogWrite(6, i);
    delay(20);
  }
  for (int i = 255; i >= 0; i-=5) {
    analogWrite(6, i);
    delay(20);
  }
}
