void Freigabe_Check() {
  if (!Ueberstrom && !Bremse && Zuendung && !Uebertemperatur && !Untertemperatur && !AnalogSensorFehler && !Temperatursensor_Fehler && Gaspedal_angeschlossen) {
    Freigabe = true;
  }
  else {
    Freigabe = false;
    Sollwert = 0;
    Sollwert_PID = 0;
  }
  MotorSteuerung();
  digitalWrite(Freigabe_PIN_Leuchte, Freigabe);
}
