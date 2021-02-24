void Rueckwaerts_auslesen() {
  volatile bool Rueckwaertsgang_alt = Rueckwaertsgang;
  if (Bremse && !digitalRead(Rueckwaerts_PIN)) {    //wenn der PIN LOW ist, dann Rückwärts fahren, sonst Vorwärts
    Rueckwaertsgang = true;
  }
  else {
    Rueckwaertsgang = false;
  }

  if (Rueckwaertsgang_alt != Rueckwaertsgang) {
    Gang_wechseln = true;
  }
  digitalWrite(Rueckwaerts_PIN_Leuchte, Rueckwaertsgang);   //Lampe Leuchtet, wenn Rückwärtsgang eingelegt ist
}


void Gang_Wechsel() {
  Gang_wechseln = false;
  if (Rueckwaertsgang) {
    digitalWrite(Spule_Vorwaerts, LOW);
    Strom_hex = map(MAX_VALUE_CURRENT_RUECKWAERTS, 0, 434, 0x00, 0x7F);
    Serial.write(byte(0x82));   //Current Limit
    Serial.write(byte(Strom_hex));
    delay (250);
    digitalWrite(Spule_Rueckwaerts, HIGH);
  }
  else {
    digitalWrite(Spule_Rueckwaerts, LOW);
    Sport_Modus_auslesen();
    delay (250);
    digitalWrite(Spule_Vorwaerts, HIGH);
  }
}
