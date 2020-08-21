void Sport_Modus_auslesen() {
  bool Sport_Modus_alt = Sport_Modus;
  Sport_Modus = !digitalRead(Sportmodus_PIN);  //Wenn PIN HIGH dann kein Sport Modus
  if (Sport_Modus_alt != Sport_Modus) {
    digitalWrite(Sport_Modus_PIN_Leuchte, Sport_Modus);
    if (Sport_Modus) {
      Periode = Prescaler / Frequenz_Sport;
      MAX_VALUE = MAX_VALUE_SPORT;
      MIN_VALUE = MIN_VALUE_SPORT;
    }
    else {
      Periode = Prescaler / Frequenz_Low;
      MAX_VALUE = MAX_VALUE_LOW;
      MIN_VALUE = MIN_VALUE_LOW;
    }
    Timer1.initialize(Periode);  //
    Timer1.start();
    Timer1.disablePwm(MOSFET_PIN);
  }

}

void Sport_Modus_firstscan() {
  Timer1.initialize(Periode);
  Timer1.start();
  Timer1.disablePwm(MOSFET_PIN);
}
