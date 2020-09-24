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
  Sollwert_analog = readChannel(ADS1115_COMP_2_GND); // 
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

void Strom_messen () {
  float Strom_intern = readChannel(ADS1115_COMP_0_GND);
  Strom = mapfloat(Strom_intern, 0.0, 5000.0, 0.0, 400.0);   //alles float's
}

void Batteriespannung_messen () {
  float Batteriespannung_intern = readChannel(ADS1115_COMP_1_GND);
  Batteriespannung = mapfloat(Batteriespannung_intern, 0.0, 5000, 0.0, 100.0);  //Wert 100 anpassen!! Maximale Spannung die 5000mV ergibt, abhängig vom Widerstand
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

float mapfloat(float x, float in_min, float in_max, float out_min, float out_max)
{
  return ((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min);
}
