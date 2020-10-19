#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


int EinschaltZeit = 45;
int analogWert;
bool letzterZustand = false;
bool aktuellerZustand = false;
int minimal = 1;
int maximal = 200;


void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Wire.setClock(1000);
  pinMode(5, OUTPUT);
  pinMode(3, INPUT_PULLUP);
  pinMode(A0, INPUT);
  
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  
  // Clear the buffer
  display.clearDisplay();
  display.display();
}

void loop() {
  // put your main code here, to run repeatedly:
  analog();
  Display();
  display.display();
  Schweissen();
}

void Display() {
  display.clearDisplay();
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font
  display.println("Standard Einschalt-");
  display.println("zeit: 45ms");
  display.println("Eingestellte Ein-");
  display.println("schaltzeit betraegt:");
  display.setTextSize(4);      // Normal 1:1 pixel scale
  display.print(EinschaltZeit);
  display.print("ms");

}

void analog () {
  analogWert = analogRead(A0);
  EinschaltZeit = map(analogWert, 0, 1023, minimal, maximal);
}

void Schweissen () {
  aktuellerZustand = !digitalRead(3);
  if (aktuellerZustand && !letzterZustand) {
    digitalWrite(5, HIGH);
    delay(EinschaltZeit);
    digitalWrite(5, LOW);
    delay(1000);
  }
  letzterZustand = aktuellerZustand;
  delay(1);
}
