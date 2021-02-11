#include<ADS1115_WE.h>
#include<Wire.h>
int Sollwert_analog;
//####I2C Adressen & AnalogSensor
#define I2C_ADDRESS 0x48


ADS1115_WE adc(I2C_ADDRESS);

void setup() {
  // put your setup code here, to run once:

  Wire.begin();
  adc.init();
  adc.setVoltageRange_mV(ADS1115_RANGE_6144);   //maximal 5000 mV
  adc.setConvRate(ADS1115_860_SPS);
  adc.setVoltageRange_mV(ADS1115_RANGE_6144);
  adc.setMeasureMode(ADS1115_SINGLE);
  adc.setVoltageRange_mV(ADS1115_RANGE_6144);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  Sollwert_analog = readChannel(ADS1115_COMP_0_GND);
  Serial.println(Sollwert_analog);
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
