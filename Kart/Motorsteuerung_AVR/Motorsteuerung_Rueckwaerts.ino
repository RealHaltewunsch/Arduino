void Rueckwaerts_auslesen() {
  if (!firstscan) {
    if (Bremse && State != 0) {    //wenn der PIN HIGH ist, dann wechseln, sonst so weiter
      Rueckwaertsgang = !Rueckwaertsgang;
      Gang_wechseln = true;
      Neutral = false;
      detachInterrupt(digitalPinToInterrupt(Rueckwaerts_PIN));
    }
  }
  firstscan = false;
}


void Gang_Wechsel() {
  if (!Neutral) {
    digitalWrite(Rueckwaerts_PIN_Leuchte, Rueckwaertsgang);   //Lampe Leuchtet, wenn Rückwärtsgang eingelegt ist
    if (Rueckwaertsgang) {
      digitalWrite(Spule_Vorwaerts, LOW);
      Serial.write(byte(0x82));   //Current Limit
      Serial.write(byte(Strom_Rueckwaerts_hex));
      delay (250);
      digitalWrite(Spule_Rueckwaerts, HIGH);
    }
    else {
      digitalWrite(Spule_Rueckwaerts, LOW);
      Serial.write(byte(0x82));   //Current Limit
      Serial.write(byte(Strom_hex));
      delay (250);
      digitalWrite(Spule_Vorwaerts, HIGH);
    }
    previousMillis_Inaktiv = currentMillis;
  }
  else {
    digitalWrite(Spule_Rueckwaerts, LOW);
    digitalWrite(Spule_Vorwaerts, LOW);
    Rueckwaertsgang = true; //so wird beim wieder einschalten wieder der Vorwärtsgang eingelegt
  }
  Gang_wechseln = false;
  firstscan = true;
  attachInterrupt(digitalPinToInterrupt(Rueckwaerts_PIN), Rueckwaerts_auslesen, FALLING);
}
