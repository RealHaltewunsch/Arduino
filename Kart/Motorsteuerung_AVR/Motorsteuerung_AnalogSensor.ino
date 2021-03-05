void  Gaspedal () {
  Sollwert_analog = analogRead(A0); //
  if (Sollwert_analog > GASPEDAL_MIN && !Gang_wechseln) {
    Sollwert_hex = map (Sollwert_analog, GASPEDAL_MIN, GASPEDAL_MAX, 0x00, 0x7F);  //analogWrite Wert absolut gesehen
    previousMillis_Inaktiv = currentMillis;
  }
  else {
    Sollwert_hex = 0x00;
  }
  Serial.write(byte(0x80));    //Speed Command
  Serial.write(byte(Sollwert_hex));    //Wert von oben
}

void Gaspedal_check () {
  Gaspedal_angeschlossen = !digitalRead(Gaspedal_check_PIN); //Gaspedal Pin low wenn angeschlossen
  Freigabe_Check();
}
