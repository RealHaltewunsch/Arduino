void Stromreglung_auslesen() {
  if (!digitalRead(Stromregelung_PIN) && !Notbetrieb) {
    Stromregelung = true;
    StromPID.SetMode(AUTOMATIC);
    else {
      Stromregelung = false;
      StromPID.SetMode(MANUAL);
    }
    digitalWrite(Stromregelung_PIN_Leuchte, Stromregelung);
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
