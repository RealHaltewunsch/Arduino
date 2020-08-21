void Sport_Modus_auslesen() {
  Sport_Modus = !digitalRead(Sportmodus_PIN);  //Wenn PIN HIGH dann kein Sport Modus
  analogWrite(MOSFET_PIN, 0);
  digitalWrite(Sport_Modus_PIN_Leuchte, Sport_Modus);
  if (Sport_Modus) {
    analogWriteFrequency(Frequenz_Sport);  //10Khz im Sportmodus
    MAX_VALUE = MAX_VALUE_SPORT;
    MIN_VALUE = MIN_VALUE_SPORT;
    MAX_VALUE_CURRENT = MAX_VALUE_CURRENT_SPORT;
  }
  else {
    analogWriteFrequency(Frequenz_Low);   //5kHz im langsamen Modus
    MAX_VALUE = MAX_VALUE_LOW;
    MIN_VALUE = MIN_VALUE_LOW;
    MAX_VALUE_CURRENT = MAX_VALUE_CURRENT_LOW;
  }
}
