void Regenerativbremsen_auslesen () {
  int Strom_regen_alt = Strom_regen;
  Regenerativbremsen = !digitalRead(Regenerativbremsen_PIN);
  digitalWrite(Regenerativbremsen_PIN_Leuchte, Regenerativbremsen);
  if (Regenerativbremsen && Sport_Modus) {
    Strom_regen = map(Regen_on_Sport, 0, 434, 0, 127);
  }
  else if (Regenerativbremsen && !Sport_Modus) {
    Strom_regen = map(Regen_on, 0, 434, 0, 127);

  }
  else {
    Strom_regen = map(Regen_off, 0, 434, 0, 127);
  }

  if (Strom_regen_alt != Strom_regen) {
    SEND(REGEN, Strom_regen);
  }
}
