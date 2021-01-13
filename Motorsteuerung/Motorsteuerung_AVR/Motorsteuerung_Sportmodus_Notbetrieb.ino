void Sport_Modus_auslesen() {
  int Strom_hex_alt = Strom_hex;
  if (digitalRead(Notbetrieb_PIN) && !digitalRead(Sportmodus_PIN)) { //Wenn PIN HIGH dann kein Sport Modus
    Sport_Modus = true;
    Strom_hex = map(MAX_VALUE_CURRENT_SPORT, 0, 438, 0x00, 0x7F);
  }
  else if (digitalRead(Notbetrieb_PIN) && digitalRead(Sportmodus_PIN)) {
    Sport_Modus = false;
    Strom_hex = map(MAX_VALUE_CURRENT_LOW, 0, 438, 0x00, 0x7F);   //Sportmodus deaktiviert, Notbetrieb aus
  }
  else {
    Sport_Modus = false;  //Sportmodus wird false, weil Notbetrieb aktiviert ist, anderen beiden Bedingungen treffen nicht zu, Frequenz wird von der ISR Notbetrieb_auslesen verändert
    Strom_hex = map(MAX_VALUE_CURRENT_NOTBETRIEB, 0, 438, 0x00, 0x7F);
  }
  digitalWrite(Sport_Modus_PIN_Leuchte, Sport_Modus);
  if (Strom_hex_alt != Strom_hex ) {
    Serial.write(byte(0x82));   //Current Limit
    Serial.write(byte(Strom_hex));
  }

}

void Notbetrieb_auslesen () {
  if (!digitalRead(Notbetrieb_PIN)) {
    Notbetrieb = true; //Wenn PIN HIGH dann kein Notbetrieb
  }
  else {
    Notbetrieb = false;
  }
  digitalWrite(Notbetrieb_PIN_Leuchte, Notbetrieb);
  Sport_Modus_auslesen(); //Aktualsiert den Sportmodus Lampe und Modus

}
