bool testb = false;
void setup() {
  // put your setup code here, to run once:
pinMode(PA0, INPUT_PULLUP);
pinMode(PC13,OUTPUT);
attachInterrupt(digitalPinToInterrupt(PA0), test, FALLING);
}

void loop() {
  // put your main code here, to run repeatedly:

delay(2000);
}

void test() {
  testb = !testb;
  digitalWrite(PC13,testb);
}
