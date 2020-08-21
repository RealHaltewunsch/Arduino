void Bremse_Funktion () {
  Timer1.disablePwm(MOSFET_PIN);
  Bremse = true;
}

void Bremse_auslesen () {
  Bremse = digitalRead(Bremse_PIN); //Wenn PIN HIGH dann Bremse gerückt
}
