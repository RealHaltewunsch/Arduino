void NOTAUS_Funktion () {
  Timer1.disablePwm(MOSFET_PIN);
  NOTAUS = true;
}

void NOTAUS_auslesen() {
  NOTAUS = digitalRead(NOTAUS_PIN);  //NOTAUS_PIN HIGH bedeutet NOT-AUS gedrückt
}
