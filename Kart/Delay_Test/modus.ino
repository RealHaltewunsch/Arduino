void modus() {
  if (Notbetrieb && !Sportmodus_state) { //Wenn PIN HIGH dann kein Sport Modus
    Sport_Modus = true;
    Strom = map(MAX_VALUE_CURRENT_SPORT, 0, 434, 0, 127);
  }
  else if (Notbetrieb && Sportmodus_state) {
    Sport_Modus = false;
    Strom = map(MAX_VALUE_CURRENT_LOW, 0, 434, 0, 127);   //Sportmodus deaktiviert, Notbetrieb aus
  }
  else {
    Sport_Modus = false;  //Sportmodus wird false, weil Notbetrieb aktiviert ist, anderen beiden Bedingungen treffen nicht zu, Frequenz wird von der ISR Notbetrieb_auslesen verändert
    Strom = map(MAX_VALUE_CURRENT_NOTBETRIEB, 0, 434, 0, 127);
  }
}
