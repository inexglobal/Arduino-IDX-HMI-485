void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  int x = analogRead(A0);
  Serial.print("A0: ");
  Serial.println(x);
  delay(500);
}
