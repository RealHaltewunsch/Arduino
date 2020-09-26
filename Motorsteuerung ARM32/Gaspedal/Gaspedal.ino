#include "ssd1306.h"
#include<ADS1115_WE.h>
#include<Wire.h>
int Sollwert_analog;
//####I2C Adressen & AnalogSensor
#define I2C_ADDRESS 0x48


ADS1115_WE adc(I2C_ADDRESS);

void setup() {
  // put your setup code here, to run once:
ssd1306_128x64_i2c_init();
  ssd1306_clearScreen();
  Wire.begin();
  adc.init();
  adc.setVoltageRange_mV(ADS1115_RANGE_6144);   //maximal 5000 mV
  adc.setConvRate(ADS1115_860_SPS);
  adc.setVoltageRange_mV(ADS1115_RANGE_6144);
  adc.setMeasureMode(ADS1115_SINGLE);
  adc.setVoltageRange_mV(ADS1115_RANGE_6144);
}

void loop() {
  // put your main code here, to run repeatedly:

  Sollwert_analog = readChannel(ADS1115_COMP_2_GND);
  OLED_Display();
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
   ssd1306_clearScreen();
  char Gaspedal_char[7];
  sprintf(Gaspedal_char, "%d", Sollwert_analog);
 
  ssd1306_setFixedFont(ssd1306xled_font6x8);  //5x7, 6x8
  ssd1306_setFixedFont(ssd1306xled_font8x16);
  ssd1306_printFixed2x(10,  10, Gaspedal_char, STYLE_BOLD);

}
