void NOTAUS_Funktion () {
  NOTAUS = digitalRead(NOTAUS_PIN);  //NOTAUS_PIN HIGH bedeutet NOT-AUS gedrückt
  if (NOTAUS) {
    Sollwert = 0;
    Sollwert_PID = 0;
    analogWrite(MOSFET_PIN, Sollwert);
  }
  Freigabe_Check();
}
