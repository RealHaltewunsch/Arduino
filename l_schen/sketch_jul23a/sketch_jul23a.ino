int brightness = 70;    // how bright the LED is
int fadeAmount = 1;    // how many points to fade the LED by 
void setup() {
  // put your setup code here, to run once:
pinMode(3,OUTPUT);
}


void loop() {
  // set the brightness of pin 9:
  analogWrite(3, brightness);

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness <= 70 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }
  // wait for 30 milliseconds to see the dimming effect
  delay(100);
}
