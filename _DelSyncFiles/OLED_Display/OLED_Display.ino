
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_MCP4725.h>

#include <PID_v1.h>

Adafruit_MCP4725 MCP4725;

// Set this value to 9, 8, 7, 6 or 5 to adjust the resolution
#define DAC_RESOLUTION    (12)

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

double analogVoltageA0 = 0; //DAC
double analogVoltageA1 = 0; //Poti
double analogVoltageA2 = 0; //DC-DC Wandler
double analogVoltageA3 = 0; //
double Ziel_Spannung = 0;
double Spannung_Poti;
double Spannung_Referenz;
double Spannung_DCDC;
double Ziel_Spannung_DAC;
double Spannung_DCDC_Feedback;

double Kp = 100 , Ki = 1 , Kd = 0; //2/0.5/2
PID myPID(&Spannung_DCDC_Feedback, &Ziel_Spannung_DAC, &Spannung_Referenz, Kp, Ki, Kd, REVERSE);

void setup() {
  Wire.begin();
  // put your setup code here, to run once:
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  // Clear the buffer
  display.clearDisplay();
  display.display();

  MCP4725.begin(0x60);
  myPID.SetOutputLimits(0, 4095);
  myPID.SetMode(AUTOMATIC);

}

void loop() {
  // put your main code here, to run repeatedly:
  Display();
  display.display();
  DAC();

}

void DAC () {
  Spannung_Poti = analogRead(A1);
  Spannung_Referenz = Spannung_Poti * 20 / 1023;
  Spannung_DCDC = analogRead(A2);
  Spannung_DCDC_Feedback = Spannung_DCDC * 20 / 1023;
  /*if (Spannung_DCDC_Feedback < Spannung_Referenz && Ziel_Spannung_DAC > 0) {
    Ziel_Spannung_DAC = Ziel_Spannung_DAC - 1;
    }
    else if (Spannung_DCDC_Feedback > Spannung_Referenz && Ziel_Spannung_DAC < 4095) {
    Ziel_Spannung_DAC++;
    }
  */
  myPID.Compute();
  MCP4725.setVoltage(Ziel_Spannung_DAC, 0);
}



void Display() {
  display.clearDisplay();
  analogVoltageA0 = analogRead(A0);
  analogVoltageA0 = analogVoltageA0 / 204.8;
  analogVoltageA1 = analogRead(A1);
  analogVoltageA1 = analogVoltageA1 / 204.8;
  analogVoltageA2 = analogRead(A2);
  analogVoltageA2 = analogVoltageA2 / 204.8;
  display.setTextSize(1);      // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font
  display.print("Der Wert am DAC betraegt: ");
  display.print(Ziel_Spannung_DAC);
  display.println("");
  display.print("Die Spannung am Poti betraegt: ");
  display.print(analogVoltageA1);
  display.println(" Volt");
  display.print("Die Zielspannung betraegt: ");
  display.print(Spannung_Referenz);
  display.println(" Volt");
  display.print("Die Spannung am DC-DC betraegt: ");
  display.print(analogVoltageA2 * 4);
  display.println(" Volt");
}
