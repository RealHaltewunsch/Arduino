void Bremse_Funktion () {
  Bremse = digitalRead(Bremse_PIN);
  if (Bremse) {
    Sollwert = 0;
    Sollwert_PID = 0;
    analogWrite(MOSFET_PIN, Sollwert);
  }
  Freigabe_Check();
}
