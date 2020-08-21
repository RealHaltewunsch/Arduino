void  Zyklische_Aufrufe() {
  if (currentMillis - previousMillis_Abtastintervall >= Abtastintervall) {
    previousMillis_Abtastintervall = currentMillis;
    Geschwindigkeit_in_kmh = Geschwindigkeit_ausgeben();
  }
  if (currentMillis - previousMillis_Temperatur >= interval_Temperatur) {
    previousMillis_Temperatur = currentMillis;
    Ueber_Untertemperatur_auslesen();
  }
  if (currentMillis - previousMillis_Analog_Fehler >= interval_Analog_Fehler) {
    previousMillis_Analog_Fehler = currentMillis;
    AnalogSensor_Fehler(); //Zeit();
  }
}
