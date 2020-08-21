void AnalogSensor_Fehler () {
  if (!adc.init()) {
    AnalogSensorFehler_Zaehler++;
    if (AnalogSensorFehler_Zaehler >= AnalogSensorFehler_Zaehler_Speicher)
      AnalogSensorFehler = true;
  }
  else {
    AnalogSensorFehler_Zaehler = 0;
    AnalogSensorFehler = false;
  }
}


void  Gaspedal () {
  adc.setCompareChannels(ADS1115_COMP_2_GND);
  Sollwert_analog = adc.getResult_mV(); // alternative: getResult_mV for Millivolt
  if (Sollwert_analog > GASPEDAL_MIN) {
    Sollwert_relativ = constrain(Sollwert_analog, GASPEDAL_MIN, GASPEDAL_MAX);  //0-100% relativ gesehen
    Sollwert_absolut = map (Sollwert, GASPEDAL_MIN, GASPEDAL_MAX, MIN_VALUE, MAX_VALUE);  //analogWrite Wert absolut gesehen
  }
  else {
    Sollwert_absolut = 0;
    Sollwert_relativ = 0;
  }
}

void Gaspedal_check () {
  Gaspedal_angeschlossen = !digitalRead(Gaspedal_check_PIN); //Gaspedal Pin low wenn angeschlossen
  Freigabe_Check();
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
