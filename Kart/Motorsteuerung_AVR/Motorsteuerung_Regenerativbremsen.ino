void Regenerativbremsen_auslesen () {
  int Strom_regen_hex_alt = Strom_regen_hex;
  Regenerativbremsen = !digitalRead(Regenerativbremsen_PIN);
  digitalWrite(Regenerativbremsen_PIN_Leuchte, Regenerativbremsen);
  if (Regenerativbremsen && Sport_Modus) {
    Strom_regen_hex = map(Regen_on_Sport, 0, 434, 0x00, 0x7F);
  }
  else if (Regenerativbremsen && !Sport_Modus) {
    Strom_regen_hex = map(Regen_on, 0, 434, 0x00, 0x7F);

  }
  else {
    Strom_regen_hex = map(Regen_off, 0, 434, 0x00, 0x7F);
  }

  if (Strom_regen_hex_alt != Strom_regen_hex) {
    Serial.write(byte(0x83));   //Regen Current Limit
    Serial.write(byte(Strom_regen_hex));
  }
}
