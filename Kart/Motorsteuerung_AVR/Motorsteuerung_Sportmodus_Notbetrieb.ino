void Sport_Modus_auslesen() {
  int Strom_alt = Strom;
  bool Sportmodus_state = !digitalRead(Sportmodus_PIN);

  if (Notbetrieb_alt != Notbetrieb || Rueckwaertsgang_alt != Rueckwaertsgang || Sportmodus_state_alt != Sportmodus_state) {
    if (!Rueckwaertsgang) {
      if (!Notbetrieb && Sportmodus_state) { //Wenn PIN HIGH dann kein Sport Modus
        Sport_Modus = true;
        Strom = map(MAX_VALUE_CURRENT_SPORT, 0, 434, 0, 127);
      }
      else if (!Notbetrieb && !Sportmodus_state) {
        Sport_Modus = false;
        Strom = map(MAX_VALUE_CURRENT_LOW, 0, 434, 0, 127);   //Sportmodus deaktiviert, Notbetrieb aus
      }
      else {
        Sport_Modus = false;  //Sportmodus wird false, weil Notbetrieb aktiviert ist, anderen beiden Bedingungen treffen nicht zu, Frequenz wird von der ISR Notbetrieb_auslesen verändert
        Strom = map(MAX_VALUE_CURRENT_NOTBETRIEB, 0, 434, 0, 127);
      }
    }
    else {
      Sport_Modus = false;
    }
    digitalWrite(Sport_Modus_PIN_Leuchte, Sport_Modus);

  }
  if (Strom_alt != Strom && !Rueckwaertsgang) {
    SEND(CURR, Strom);
  }
  

  Notbetrieb_alt = Notbetrieb;
  Rueckwaertsgang_alt = Rueckwaertsgang;
  Sportmodus_state_alt = Sportmodus_state;

}

void Notbetrieb_auslesen () {
  if (!digitalRead(Notbetrieb_PIN)) {
    Notbetrieb = true; //Wenn PIN HIGH dann kein Notbetrieb
  }
  else {
    Notbetrieb = false;
  }
  digitalWrite(Notbetrieb_PIN_Leuchte, Notbetrieb);
}
