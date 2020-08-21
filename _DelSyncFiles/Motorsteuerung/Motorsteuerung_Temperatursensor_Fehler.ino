void TemperaturSensorFehler () {
  if (Min_Akku_Temperatur_erfragen () <= 0 || Min_Leistungselektronik_Temperatur_erfragen () <= 0 || Motor_Temperatur_erfragen () <= 0) {
    Temperatursensor_Fehler = true;
  }
  else {
    Temperatursensor_Fehler = false;
  }
}
