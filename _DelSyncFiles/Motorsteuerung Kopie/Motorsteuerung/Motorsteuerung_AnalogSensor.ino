void AnalogSensor_Fehler () {
  if (!adc.init()) {
    AnalogSensorFehler = true;
  }
  else {
    AnalogSensorFehler = true;
  }
}

float Strom () {
  adc.setCompareChannels(ADS1115_COMP_0_GND);
  float Strom_analog = adc.getResult_V(); // alternative: getResult_mV for Millivolt
  float Strom_intern = mapfloat(Strom_analog, 0.0, 5.000, 0, 400.0);
  return Strom_intern;
}
float Batteriespannung () {
  adc.setCompareChannels(ADS1115_COMP_1_GND);
  float Batteriespannung_intern = adc.getResult_V(); // alternative: getResult_mV for Millivolt
  Batteriespannung_intern = mapfloat(Batteriespannung_intern, 0.0, 5.000, 0, 100.0);  //Wert 100 anpassen!! Maximale Spannung die 5000mV ergibt, abhängig vom Widerstand
  return Batteriespannung_intern;
}

int Leistung (int U, int I) {
  int  Leistung_intern = U * I;
  return Leistung_intern;
}

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
