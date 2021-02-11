void Regenerativbremsen_Auslesen () {
  int Strom_regen_hex_alt = Strom_regen_hex;
  Regenerativbremsen = !digitalRead(Regenerativbremsen_PIN);

  if (Regenerativbremsen && Sport_Modus) {
    Strom_regen_hex = map(Regen_on_Sport, 0, 438, 0x00, 0x7F);
  }
  else if (Regenerativbremsen && !Sport_Modus) {
    Strom_regen_hex = map(Regen_on, 0, 438, 0x00, 0x7F);

  }
  else {
    Strom_regen_hex = map(Regen_off, 0, 438, 0x00, 0x7F);
  }

  if (Strom_regen_hex_alt != Strom_regen_hex) {
    Serial.write(byte(0x83));   //Regen Current Limit
    Serial.write(byte(Strom_regen_hex));
    digitalWrite(Regenerativbremsen_PIN_Leuchte, Regenerativbremsen);
  }

  if (Regen_on == Regen_on) { //wenn dass der Fall ist, sind die Werte immer die selben, dann würde die LED nicht umschalten
    digitalWrite(Regenerativbremsen_PIN_Leuchte, Regenerativbremsen);
  }
}
