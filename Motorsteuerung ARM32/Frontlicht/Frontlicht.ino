#include <Adafruit_NeoPixel.h>

#define PIN 6
#define NUMPIXELS 48  //24 Pixel verbrauchen 5,35W bei maximaler Helligkeit 
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  pixels.begin();
  pixels.clear();
  pixels.show();
  Startup();
  delay(5000);
}

void loop() {
  // put your main code here, to run repeatedly:
  /*for (int i = 0; i <= 5; i++) {
    Blinker();
    }
    for (int i = 0; i <= NUMPIXELS; i++) { // For each pixel...
    pixels.setPixelColor(i, pixels.Color(255, 255, 255));
    pixels.show();   // Send the updated pixel colors to the hardware.
    }
    delay(6666);
  */
  Party();
}

void Party () {
  pixels.setPixelColor(random(0, NUMPIXELS), pixels.Color(random(0, 255), random(0, 255), random(0, 255)));
  pixels.show();
  if ( 1 == random (0, 20) ) {
    for (int i = 0; i <= NUMPIXELS; i++) { // For each pixel...
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
      pixels.show();   // Send the updated pixel colors to the hardware.
    }
    delay (random(10, 100));
    for (int i = 0; i <= NUMPIXELS; i++) { // For each pixel...
      pixels.setPixelColor(random(0, NUMPIXELS), pixels.Color(random(0, 255), random(0, 255), random(0, 255)));
      pixels.show();   // Send the updated pixel colors to the hardware.
    }
  }
  else if ( 1 == random (0, 20) ) {
    for (int i = 0; i <= NUMPIXELS; i++) { // For each pixel...
      pixels.setPixelColor(i, pixels.Color(255, 255, 255));
      pixels.show();   // Send the updated pixel colors to the hardware.
    }
    delay (random(10, 100));
    for (int i = 0; i <= NUMPIXELS; i++) { // For each pixel...
      pixels.setPixelColor(random(0, NUMPIXELS), pixels.Color(random(0, 255), random(0, 255), random(0, 255)));
      pixels.show();   // Send the updated pixel colors to the hardware.
    }
  }
  else if ( 1 == random (0, 20) ) {
    for (int i = 0; i <= NUMPIXELS; i++) { // For each pixel...
      pixels.setPixelColor(i, pixels.Color(255, 0, 0));
      pixels.show();   // Send the updated pixel colors to the hardware.
    }
    delay (random(10, 100));
    for (int i = 0; i <= NUMPIXELS; i++) { // For each pixel...
      pixels.setPixelColor(random(0, NUMPIXELS), pixels.Color(random(0, 255), random(0, 255), random(0, 255)));
      pixels.show();   // Send the updated pixel colors to the hardware.
    }
  }
  else if ( 1 == random (0, 20) ) {
    for (int i = 0; i <= NUMPIXELS; i++) { // For each pixel...
      pixels.setPixelColor(i, pixels.Color(0, 255, 0));
      pixels.show();   // Send the updated pixel colors to the hardware.
    }
    delay (random(10, 100));
    for (int i = 0; i <= NUMPIXELS; i++) { // For each pixel...
      pixels.setPixelColor(random(0, NUMPIXELS), pixels.Color(random(0, 255), random(0, 255), random(0, 255)));
      pixels.show();   // Send the updated pixel colors to the hardware.
    }
  }
  else if ( 1 == random (0, 20) ) {
    for (int i = 0; i <= NUMPIXELS; i++) { // For each pixel...
      pixels.setPixelColor(i, pixels.Color(0, 0, 255));
      pixels.show();   // Send the updated pixel colors to the hardware.
    }
    delay (random(10, 100));
    for (int i = 0; i <= NUMPIXELS; i++) { // For each pixel...
      pixels.setPixelColor(random(0, NUMPIXELS), pixels.Color(random(0, 255), random(0, 255), random(0, 255)));
      pixels.show();   // Send the updated pixel colors to the hardware.
    }
  }
}



void Blinker () {
  for (int i = 0; i <= NUMPIXELS; i++) { // For each pixel...
    pixels.setPixelColor(i, pixels.Color(50, 50, 50));
    pixels.show();   // Send the updated pixel colors to the hardware.
    //delay(0); // Pause before next pass through loop
  }

  for (int i = 0; i <= 12; i++) { // For each pixel...
    pixels.setPixelColor(i, pixels.Color(255, 90, 0));
    pixels.show();   // Send the updated pixel colors to the hardware.
    //delay(0); // Pause before next pass through loop
  }
  delay(666);
  for (int i = 12; i >= 0; i--) { // For each pixel...

    pixels.setPixelColor(i, pixels.Color(50, 50, 50));
    pixels.show();   // Send the updated pixel colors to the hardware.
    //delay(0); // Pause before next pass through loop
  }
  delay(666);
}

void Startup() {
  int i = 0;
  int j = NUMPIXELS - 1;

  while (i <= NUMPIXELS / 2 && j >= NUMPIXELS / 2) {
    pixels.setPixelColor(i, pixels.Color(255, 255, 255));
    pixels.setPixelColor(j, pixels.Color(255, 255, 255));
    pixels.show();   // Send the updated pixel colors to the hardware.
    i++;
    j--;
    delay(25); // Pause before next pass through loop

  }






}
