void Zuendung_auslesen() {
  Zuendung = !digitalRead(Zuendung_PIN);  //Wenn PIN HIGH dann Zündung nicht gedrückt
  digitalWrite(Zuendung_PIN_Leuchte, Zuendung);
}
