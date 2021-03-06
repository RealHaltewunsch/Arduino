
#include <Wire.h>
#include <ADXL345.h>

#include <Adafruit_NeoPixel.h>
//int d0 = 16;
int PIN = 6;
int NUMPIXELS = 12;
bool Zustand = false;   //0 ist aus, 1 ist an
short int Counter = 0;   //0 weiß leuchten, 1 rot-organge fest, 2  rot-orange wechselt langsam Farbe , 3 rot-orange mit blitzen
long int Zeit = 0;
long int previous_interval = 0;
int interval = 100;
int blitzen = 5;  //1-10 nicht 0! 1 -> wenig blitzen, 10 -> viel blitzen


ADXL345 adxl; //variable adxl is an instance of the ADXL345 library


// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin(); // Initialisierung der NeoPixel
  pixels.setPixelColor(0, pixels.Color(0, 0, 0)); // Pixel aus
  pixels.setPixelColor(1, pixels.Color(0, 0, 0)); // Pixel aus
  pixels.setPixelColor(2, pixels.Color(0, 0, 0)); // Pixel aus
  pixels.show(); // Durchführen der Pixel-Ansteuerung
  delay(1000);
  randomSeed(analogRead(0));
  adxl.powerOn();

  //set activity/ inactivity thresholds (0-255)
  adxl.setActivityThreshold(75); //62.5mg per increment
  adxl.setInactivityThreshold(75); //62.5mg per increment
  adxl.setTimeInactivity(10); // how many seconds of no activity is inactive?

  //look of activity movement on this axes - 1 == on; 0 == off
  adxl.setActivityX(1);
  adxl.setActivityY(1);
  adxl.setActivityZ(1);

  //look of inactivity movement on this axes - 1 == on; 0 == off
  adxl.setInactivityX(1);
  adxl.setInactivityY(1);
  adxl.setInactivityZ(1);

  //look of tap movement on this axes - 1 == on; 0 == off
  adxl.setTapDetectionOnX(0);
  adxl.setTapDetectionOnY(0);
  adxl.setTapDetectionOnZ(1);

  //set values for what is a tap, and what is a double tap (0-255)
  adxl.setTapThreshold(50); //62.5mg per increment
  adxl.setTapDuration(15); //625μs per increment
  adxl.setDoubleTapLatency(80); //1.25ms per increment
  adxl.setDoubleTapWindow(200); //1.25ms per increment

  //set values for what is considered freefall (0-255)
  adxl.setFreeFallThreshold(7); //(5 - 9) recommended - 62.5mg per increment
  adxl.setFreeFallDuration(45); //(20 - 70) recommended - 5ms per increment

  //setting all interupts to take place on int pin 1
  //I had issues with int pin 2, was unable to reset it
  adxl.setInterruptMapping( ADXL345_INT_SINGLE_TAP_BIT,  ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_DOUBLE_TAP_BIT,  ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_FREE_FALL_BIT,  ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_ACTIVITY_BIT,   ADXL345_INT1_PIN );
  adxl.setInterruptMapping( ADXL345_INT_INACTIVITY_BIT,  ADXL345_INT1_PIN );

  //register interupt actions - 1 == on; 0 == off
  adxl.setInterrupt( ADXL345_INT_SINGLE_TAP_BIT, 1);
  adxl.setInterrupt( ADXL345_INT_DOUBLE_TAP_BIT, 1);
  adxl.setInterrupt( ADXL345_INT_FREE_FALL_BIT, 1);
  adxl.setInterrupt( ADXL345_INT_ACTIVITY_BIT,  1);
  adxl.setInterrupt( ADXL345_INT_INACTIVITY_BIT, 1);
}

void loop() {
  Zeit = millis();

  if (Zustand) {


    if (Counter == 0)   //weiß leuchten
    {
      for (int xy = 0; xy <=  NUMPIXELS; xy++) {
        pixels.setPixelColor(xy, pixels.Color(255, 255, 255)); // color
      }
      pixels.show();

    }
    if (Counter == 1) //rot-orange fest
    {
      for (int xz = 0; xz <=  NUMPIXELS; xz++) {
        pixels.setPixelColor(xz, pixels.Color(255, 60, 5)); // color
      }
      pixels.show();

    }
    if (Zeit - previous_interval >= interval) {

      previous_interval = Zeit;

      if (Counter == 2) //rot-orange wechseln
      {
        Ring(random(0, NUMPIXELS));
      }

      if (Counter == 3) //rot-orange mit blitzen
      {
        Ring(random(0, NUMPIXELS));
        if (random(0, interval / blitzen) == 1) {
          blitzen_Ring(random(0, NUMPIXELS));
        }
      }
    }

  }
  else {
    for (int zz = 0; zz <=  NUMPIXELS; zz++) {
      pixels.setPixelColor(zz, pixels.Color(0, 0, 0)); // color

    }
    pixels.show();
  }
  //Boring accelerometer stuff
  int x, y, z;
  adxl.readAccel(&x, &y, &z); //read the accelerometer values and store them in variables x,y,z

  //Fun Stuff!
  //read interrupts source and look for triggerd actions
  //getInterruptSource clears all triggered actions after returning value
  //so do not call again until you need to recheck for triggered actions
  byte interrupts = adxl.getInterruptSource();

  // freefall
  /*if (adxl.triggered(interrupts, ADXL345_FREE_FALL)) {
    Serial.println("freefall");
    //add code here to do when freefall is sensed
    }
    //inactivity
    if (adxl.triggered(interrupts, ADXL345_INACTIVITY)) {
    Serial.println("inactivity");
    //add code here to do when inactivity is sensed
    }

    //activity
    if (adxl.triggered(interrupts, ADXL345_ACTIVITY)) {
    Serial.println("activity");
    //add code here to do when activity is sensed
    }
  */
  //double tap
  if (adxl.triggered(interrupts, ADXL345_DOUBLE_TAP)) {
    Serial.println("double tap");
    //add code here to do when a 2X tap is sensed
    Zustand = !Zustand;   //wechsel von Aus nach An und so weiter
    Counter++;
    if (Counter >= 4) {
      Counter = 0;
    }
    

  }

  //tap
  if (adxl.triggered(interrupts, ADXL345_SINGLE_TAP)) {
    Serial.println("tap");
    //add code here to do when a tap is sensed
    Counter++;
    if (Counter >= 4) {
      Counter = 0;
    }
  }

}// Ende Loop

void Ring(int i) {
  pixels.setPixelColor(i, pixels.Color(random(230, 255), random(0, 90), random(0, 5))); // color
  pixels.show();
}

void blitzen_Ring(int i) {
  int a = 200;
  int b = 230;
  int z2 = random(0,NUMPIXELS);
  pixels.setPixelColor(i, pixels.Color(random(a, b), random(a, b), random(a, b))); // color
  pixels.setPixelColor(z2, pixels.Color(random(a, b), random(a, b), random(a, b))); // color
  pixels.show();
  delay(200);
  pixels.setPixelColor(i, pixels.Color(random(230, 255), random(0, 50), random(0, 5))); // color
  pixels.setPixelColor(z2, pixels.Color(random(230, 255), random(0, 50), random(0, 5))); // color
  pixels.show();

}
