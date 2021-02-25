void Rueckwaerts_auslesen() {
  volatile bool Rueckwaertsgang_alt = Rueckwaertsgang;
  if (Bremse) {    //wenn der PIN LOW ist, dann Rückwärts fahren, sonst Vorwärts
    Rueckwaertsgang = !Rueckwaertsgang;
    Gang_wechseln = true;
    digitalWrite(Rueckwaerts_PIN_Leuchte, Rueckwaertsgang);   //Lampe Leuchtet, wenn Rückwärtsgang eingelegt ist

  }
}


void Gang_Wechsel() {
  if (Rueckwaertsgang && State != 0) {
    digitalWrite(Spule_Vorwaerts, LOW);
    Strom_hex = map(MAX_VALUE_CURRENT_RUECKWAERTS, 0, 434, 0x00, 0x7F);
    Serial.write(byte(0x82));   //Current Limit
    Serial.write(byte(Strom_hex));
    delay (250);
    digitalWrite(Spule_Rueckwaerts, HIGH);
    Gang_wechseln = false;
  }
  else if (!Rueckwaertsgang && State != 0) {
    digitalWrite(Spule_Rueckwaerts, LOW);
    Sport_Modus_auslesen();
    delay (250);
    digitalWrite(Spule_Vorwaerts, HIGH);
    Gang_wechseln = false;
  }
  else if (State == 0) {
    digitalWrite(Spule_Rueckwaerts, HIGH);
    digitalWrite(Spule_Vorwaerts, HIGH);
  }
}
