void setup() {
  // put your setup code here, to run once:
pinMode(PA0,OUTPUT);
analogWriteResolution (16);
  analogWriteFrequency(10000); // Set PMW period to 2000 Hz instead of 1000
}

void loop() {
  // put your main code here, to run repeatedly:
analogWrite(PA0,30000);
}
