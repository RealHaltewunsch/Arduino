void Rueckwaerts_auslesen() {
  if (!digitalRead(Rueckwaerts_PIN) && Bremse && State != 0) {
    Rueckwaerts_Zaehler++;
  }
  else {
    Rueckwaerts_Zaehler = 0;
  }

  if (Rueckwaerts_Zaehler == 8) {    //0,8 Sekunde am Stück der Knopf gedrückt ist in den Rückwärtsgang schalten
    Rueckwaertsgang = !Rueckwaertsgang;
    Gang_wechseln = true;
    Neutral = false;
  }
  else if (Rueckwaerts_Zaehler == 20) {    //1,6 Sekunde am Stück der Knopf gedrückt ist in den Rückwärtsgang schalten
    Rueckwaertsgang = !Rueckwaertsgang;
    Gang_wechseln = true;
    Neutral = true;
  }
}


void Gang_Wechsel() {
  if (!Neutral) {
    digitalWrite(Rueckwaerts_PIN_Leuchte, Rueckwaertsgang);   //Lampe Leuchtet, wenn Rückwärtsgang eingelegt ist
    if (Rueckwaertsgang) {
      digitalWrite(Spule_Vorwaerts, LOW);
      SEND(CURR, Strom_Rueckwaerts);
      delay (250);
      digitalWrite(Spule_Rueckwaerts, HIGH);
    }
    else {
      digitalWrite(Spule_Rueckwaerts, LOW);
      SEND(CURR, Strom);
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
