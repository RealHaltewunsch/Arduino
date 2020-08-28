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
  if (!Ueberstrom && Zuendung && !Uebertemperatur && !Untertemperatur && !AnalogSensorFehler && !Temperatursensor_Fehler && Gaspedal_angeschlossen) {
    Freigabe_lite = true; //Freigabe lite ist true, wenn alles i.O. ist, aber die Bremse gedrückt wird. Dadurch schaltet der Bidlschirm nicht um. Es wird weiterhin die Geschwindigkeit angezeigt
  }
  else {
    Freigabe_lite = false;
  }
  digitalWrite(Freigabe_PIN_Leuchte, Freigabe);
}
