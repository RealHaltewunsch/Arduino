#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Fonts/myownfont.h>
#include <stdlib.h>
#include<ADS1115_WE.h>
#include<Wire.h>
int Sollwert_analog;
//####I2C Adressen & AnalogSensor
//I2C Pins: 20 (SDA), 21 (SCL) //für den Display und analog Sensor interessant
#define I2C_ADDRESS 0x48    //Adresse für den AnalogSensor
#define OLED_ADDR   0x3C
Adafruit_SSD1306 display(-1);

ADS1115_WE adc(I2C_ADDRESS);

void setup() {
  // put your setup code here, to run once:

  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.display();
  adc.init();
  adc.setVoltageRange_mV(ADS1115_RANGE_6144);   //maximal 5000 mV
  adc.setConvRate(ADS1115_860_SPS);
  adc.setVoltageRange_mV(ADS1115_RANGE_6144);
  adc.setMeasureMode(ADS1115_SINGLE);
  adc.setVoltageRange_mV(ADS1115_RANGE_6144);
}

void loop() {
  // put your main code here, to run repeatedly:

  Sollwert_analog = readChannel(ADS1115_COMP_0_GND);
  OLED_Display();
  display.display();
  delay(1000);
}


int readChannel(ADS1115_MUX channel) {
  adc.setVoltageRange_mV(ADS1115_RANGE_6144);
  int voltage = 0;
  adc.setCompareChannels(channel);
  adc.startSingleMeasurement();
  while (adc.isBusy()) {}
  voltage = adc.getResult_mV(); // alternative: getResult_mV for Millivolt
  return voltage;
}


void OLED_Display() {
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setFont(&Dialog_plain_12);
  display.setCursor(10, 10);
  display.println(Sollwert_analog);

}
