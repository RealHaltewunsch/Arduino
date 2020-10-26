void Freigabe_Check() {
  if (Zuendung && !Uebertemperatur && !Untertemperatur && !AnalogSensorFehler && !Temperatursensor_Fehler && Gaspedal_angeschlossen) {
    Freigabe = true;
  }
  else {
    Freigabe = false;
  }
  digitalWrite(Freigabe_PIN_Leuchte, Freigabe);
  
}
