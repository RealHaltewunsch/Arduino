void Stromreglung_auslesen () {
if (!digitalRead(Stromregelung_PIN) && !Notbetrieb) {
  Stromregelung = true;
  else {
    Stromregelung = false;
  }
  digitalWrite(Stromregelung_PIN_Leuchte, Stromregelung);
  if (Stromregelung) {
    StromPID.SetMode(AUTOMATIC);
  }
  else {
    StromPID.SetMode(MANUAL);
  }
  return;
}

void PID_Regler() { //aufruf nur wenn Stromregelung = true
  //zuvor muss sichergestellt werden dass die Variable Input aktualisiert ist!!
  Strom_messen();
  Messwert_Gaspedal = map(Sollwert_relativ, GASPEDAL_MIN, GASPEDAL_MAX, 0, MAX_VALUE_CURRENT);
  Messwert_Strom = Strom;
  StromPID.Compute();  //das verändert die Variable Sollwert_PID
  //Messwert_Strom, Sollwert_PID, Messwert_Gaspedal ANPASSEN
  return;
}
