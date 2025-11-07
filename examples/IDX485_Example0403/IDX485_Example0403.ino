void setup() {
  // put your setup code here, to run once:
  pinMode(1, INPUT_PULLUP);
  pinMode(10, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int x = digitalRead(1);
  digitalWrite(10, x);
}
