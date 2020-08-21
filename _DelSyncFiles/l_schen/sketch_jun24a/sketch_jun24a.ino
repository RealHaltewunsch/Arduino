/*
  Fade

  This example shows how to fade an LED on pin 9 using the analogWrite()
  function.

  The analogWrite() function uses PWM, so if you want to change the pin you're
  using, be sure to use another PWM capable pin. On most Arduino, the PWM pins
  are identified with a "~" sign, like ~3, ~5, ~6, ~9, ~10 and ~11.

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Fade
*/

int led = 13;           // the PWM pin the LED is attached to
int brightness = 20;    // how bright the LED is
int fadeAmount = 1;    // how many points to fade the LED by
int ledb = 12;           // the PWM pin the LED is attached to
int brightnessb = 20;    // how bright the LED is
int fadeAmountb = 1;    // how many points to fade the LED by

// the setup routine runs once when you press reset:
void setup() {
  // declare pin 13 to be an output:
  pinMode(led, OUTPUT);
  pinMode(ledb, OUTPUT);
  digitalWrite(led, HIGH);
  digitalWrite(ledb, HIGH);
  delay(1000);
  digitalWrite(led, LOW);
  digitalWrite(ledb, LOW);
}

// the loop routine runs over and over again forever:
void loop() {
  // set the brightness of pin 9:
  analogWrite(led, brightness);

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness <= 0 || brightness >= 255) {
    fadeAmount = -fadeAmount;
  }
  // wait for 30 milliseconds to see the dimming effect
  delay(20);

  /*Blaue LED*/
  analogWrite(ledb, brightnessb);

  // change the brightness for next time through the loop:
  brightnessb = brightnessb + fadeAmountb;

  // reverse the direction of the fading at the ends of the fade:
  if (brightnessb <= 0 || brightnessb >= 255) {
    fadeAmountb = -fadeAmountb;
  }
  // wait for 30 milliseconds to see the dimming effect
  delay(20);
}
