int brightness = 0x00;    // how bright the LED is
int fadeAmount = 0x1;    // how many points to fade the LED by


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.write(byte(0xE0));
  Serial.write(byte(0x8A));
  Serial.write(byte(0x00));
  Serial.write(byte(0x84)); //accel limit
  Serial.write(byte(0x00)); //min
  Serial.write(byte(0x85)); //decel limit
  Serial.write(byte(0x00)); //min
  delay(2500);
  Serial.write(byte(0x8A));
  Serial.write(byte(0x01));
}

void loop() {
  // put your main code here, to run repeatedly:

  /*Serial.write(byte(0x80));
  //int ran = random(0x00, 0x7F);
  Serial.write(byte(0x7F));
  delay(1000);
  Serial.write(byte(0x80));
  Serial.write(byte(0x2F));
  delay(1000);
  Serial.write(byte(0x80));
  Serial.write(byte(0x00));
  delay(1000);
  */


 Serial.write(byte(0x80));
  Serial.write(byte(brightness));

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness <= 0x00 || brightness >= 0x7F) {
    fadeAmount = -fadeAmount;
  }
  // wait for 30 milliseconds to see the dimming effect
  delay(100);

  
}
