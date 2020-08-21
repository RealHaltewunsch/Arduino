int d1 = 5;

void setup() {
  // put your setup code here, to run once:
pinMode(d1, OUTPUT);
//analogWriteFreq(50000);
}

void loop() {
  // put your main code here, to run repeatedly:
analogWrite(d1,512);
}
