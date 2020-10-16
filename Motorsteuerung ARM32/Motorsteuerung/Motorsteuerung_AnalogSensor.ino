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
    Sollwert_hex = map (Sollwert_relativ, GASPEDAL_MIN, GASPEDAL_MAX, 0x00, 0x7F);  //analogWrite Wert absolut gesehen
  }
  else {
    Sollwert_hex = 0x00;
  }
  Serial1.write(0x80);    //Speed Command
  Serial1.write(Sollwert_hex);    //Wert von oben
}

void Gaspedal_check () {
  Gaspedal_angeschlossen = !digitalRead(Gaspedal_check_PIN); //Gaspedal Pin low wenn angeschlossen
  Freigabe_Check();
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
