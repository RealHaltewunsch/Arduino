void Zuendung_auslesen() {
  Zuendung = !digitalRead(Zuendung_PIN);  //Wenn PIN HIGH dann Zündung aus
  digitalWrite(Zuendung_PIN_Leuchte, Zuendung);
  digitalWrite(Enable_Pin, !Zuendung);
  Freigabe_Check();
  Notbetrieb_auslesen ();
  return;
}
