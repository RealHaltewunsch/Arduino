void Sport_Modus_auslesen() {

  if (digitalRead(Notbetrieb_PIN) && !digitalRead(Sportmodus_PIN)) { //Wenn PIN HIGH dann kein Sport Modus
    Sport_Modus = true;
    if (Sport_Modus) {
      analogWriteFrequency(Frequenz_Sport);  //10Khz im Sportmodus
      MAX_VALUE = MAX_VALUE_SPORT;
      MIN_VALUE = MIN_VALUE_SPORT;
      MAX_VALUE_CURRENT = MAX_VALUE_CURRENT_SPORT;
      StromPID.SetOutputLimits(MIN_VALUE, MAX_VALUE);
    }
  }
  else if (digitalRead(Notbetrieb_PIN) && digitalRead(Sportmodus_PIN)) {
    Sport_Modus = false;
    analogWriteFrequency(Frequenz_Low);   //5kHz im langsamen Modus
    MAX_VALUE = MAX_VALUE_LOW;
    MIN_VALUE = MIN_VALUE_LOW;
    MAX_VALUE_CURRENT = MAX_VALUE_CURRENT_LOW;
    StromPID.SetOutputLimits(MIN_VALUE, MAX_VALUE);
  }
  else {
    Sport_Modus = false;  //Sportmodus wird false, weil Notbetrieb aktiviert ist, anderen beiden Bedingungen treffen nicht zu, Frequenz wird von der ISR Notbetrieb_auslesen verändert
  }
  digitalWrite(Sport_Modus_PIN_Leuchte, Sport_Modus);
  return;
}

void Notbetrieb_auslesen () {
  if (!digitalRead(Notbetrieb_PIN) && Zuendung)
    Notbetrieb = true; //Wenn PIN HIGH dann kein Notbetrieb
}
else {
  Notbetrieb = false;
}
digitalWrite(Notbetrieb_PIN_Leuchte, Notbetrieb);

if (Notbetrieb) {
  analogWriteFrequency(Frequenz_Notbetrieb);  //2Khz im Notbetrieb
  MAX_VALUE = MAX_VALUE_NOTBETRIEB;
  MIN_VALUE = MIN_VALUE_NOTBETRIEB;
  MAX_VALUE_CURRENT = MAX_VALUE_CURRENT_NOTBETRIEB;
  StromPID.SetOutputLimits(MIN_VALUE, MAX_VALUE);
}
Sport_Modus_auslesen(); //Aktualsiert den Sportmodus Lampe und Modus
Stromreglung_auslesen();  //Aktualisiert die Notbetrieb Lampe und Modus  
return;
}
