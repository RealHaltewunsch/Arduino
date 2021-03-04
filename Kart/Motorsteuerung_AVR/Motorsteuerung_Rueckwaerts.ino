void Rueckwaerts_auslesen() {
  if (Strom_Rueckwaerts_hex != 0) {
    if (Bremse) {    //wenn der PIN HIGH ist, dann qwchseln, sonst so weiter
      Rueckwaertsgang = !Rueckwaertsgang;
      Gang_wechseln = true;
      Neutral = false;
    }
  }
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
      Gang_wechseln = false;
    }
    else {
      digitalWrite(Spule_Rueckwaerts, LOW);
      Serial.write(byte(0x82));   //Current Limit
      Serial.write(byte(Strom_hex));
      delay (250);
      digitalWrite(Spule_Vorwaerts, HIGH);
      Gang_wechseln = false;
    }
    previousMillis_Inaktiv = currentMillis;
  }
  else {
    digitalWrite(Spule_Rueckwaerts, LOW);
    digitalWrite(Spule_Vorwaerts, LOW);
    Gang_wechseln = false;
  }
}
