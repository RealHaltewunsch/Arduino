void Regenerativbremsen_auslesen () {
  int Strom_regen_alt = Strom_regen;
  bool Regenerativbremsen_alt = Regenerativbremsen;
  Regenerativbremsen = !digitalRead(Regenerativbremsen_PIN);
  if (Regenerativbremsen_alt != Regenerativbremsen || Strom_regen == 0) {
    digitalWrite(Regenerativbremsen_PIN_Leuchte, Regenerativbremsen);
    if (Regenerativbremsen && Sport_Modus) {
      Strom_regen = Regen_on_Sport;
    }
    else if (Regenerativbremsen && !Sport_Modus) {
      Strom_regen = Regen_on;
    }
    else {
      Strom_regen = Regen_off;
    }

    if (Strom_regen_alt != Strom_regen) {
      SEND(REGEN, Strom_regen);
    }
  }
}
