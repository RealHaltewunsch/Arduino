#include <Adafruit_NeoPixel.h>

#define PIN 6
#define NUMPIXELS 24  //24 Pixel verbrauchen 5,35W bei maximaler Helligkeit 
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // put your setup code here, to run once:
  pixels.begin();
  pixels.clear();
  pixels.show();
  Startup();
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
  int j = NUMPIXELS-1;

  while (i <= NUMPIXELS / 2 && j >= NUMPIXELS / 2) {
    pixels.setPixelColor(i, pixels.Color(255, 255, 255));
    pixels.setPixelColor(j, pixels.Color(255, 255, 255));
    pixels.show();   // Send the updated pixel colors to the hardware.
    i++;
    j--;
    delay(25); // Pause before next pass through loop

  }






}
