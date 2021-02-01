void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
Serial.write(byte(0x80));
Serial.write(byte(0x30));
delay(500);
}
