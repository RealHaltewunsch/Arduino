void setup() {
  // put your setup code here, to run once:
pinMode(OUTPUT,PA3);
analogWriteResolution (16); //16-bit PWM, 0-65535
  analogWriteFrequency(10000); // PWM Frequenz von 10kHz als Standard
  
}

void loop() {
  // put your main code here, to run repeatedly:
analogWrite(PA3,65535);
delay(10000);
analogWrite(PA3,32767);
delay(10000);
analogWrite(PA3,5000);
delay(10000);
analogWrite(PA3,0);
delay(10000);
}
