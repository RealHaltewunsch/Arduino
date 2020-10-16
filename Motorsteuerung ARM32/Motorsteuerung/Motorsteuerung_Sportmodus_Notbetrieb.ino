void Sport_Modus_auslesen() {

  if (digitalRead(Notbetrieb_PIN) && !digitalRead(Sportmodus_PIN)) { //Wenn PIN HIGH dann kein Sport Modus
    Sport_Modus = true;
    Strom_hex = map(MAX_VALUE_CURRENT_SPORT, 0, 438, 0x00, 0x7F);
  }
  else if (digitalRead(Notbetrieb_PIN) && digitalRead(Sportmodus_PIN)) {
    Sport_Modus = false;
    Strom_hex = map(MAX_VALUE_CURRENT, 0, 438, 0x00, 0x7F);
  }
  else {
    Sport_Modus = false;  //Sportmodus wird false, weil Notbetrieb aktiviert ist, anderen beiden Bedingungen treffen nicht zu, Frequenz wird von der ISR Notbetrieb_auslesen verändert
    Strom_hex = map(MAX_VALUE_CURRENT_NOTBETRIEB, 0, 438, 0x00, 0x7F);
  }
  digitalWrite(Sport_Modus_PIN_Leuchte, Sport_Modus);
  return;
}

void Notbetrieb_auslesen () {
  if (!digitalRead(Notbetrieb_PIN) && Zuendung) {
    Notbetrieb = true; //Wenn PIN HIGH dann kein Notbetrieb
    Strom_hex = map(MAX_VALUE_CURRENT_NOTBETRIEB, 0, 438, 0x00, 0x7F);
  }
  else {
    Notbetrieb = false;
  }
  digitalWrite(Notbetrieb_PIN_Leuchte, Notbetrieb);
  Sport_Modus_auslesen(); //Aktualsiert den Sportmodus Lampe und Modus
  Stromreglung_auslesen();  //Aktualisiert die Notbetrieb Lampe und Modus
  return;
}



/*
  Serial1.write(0x8A);    //Direction
  Serial1.write(0x01);    // FORWARD
  Serial1.write(0x82);    //Current Limit
  Serial1.write(0x0B);    //11 Dezimal enspricht 37,62A
  Serial1.write(0x83);    //Regen Limit
  Serial1.write(0x05);    //5 in Dezimal enspricht 17,1A
*/
