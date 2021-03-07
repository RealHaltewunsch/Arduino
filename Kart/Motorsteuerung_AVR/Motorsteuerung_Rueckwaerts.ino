void Rueckwaerts_auslesen() {
  if (!digitalRead(Rueckwaerts_PIN) && Bremse && State != 0) {
    Rueckwaerts_Zaehler++;
  }
  else {
    Rueckwaerts_Zaehler = 0;
  }

  if (Rueckwaerts_Zaehler == 4) {    //1 Sekunde am Stück der Knopf gedrückt ist in den Rückwärtsgang schalten
    Rueckwaertsgang = !Rueckwaertsgang;
    Gang_wechseln = true;
    Neutral = false;
    Rueckwaerts_Zaehler = 0;
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
}
