void Initialwerte_schreiben () {
  Regenerativbremsen = !digitalRead(Regenerativbremsen_PIN);
  if (Regenerativbremsen) {
    Strom_regen_hex = map(Regen_on, 0, 438, 0x00, 0x7F);
  }
  else {
    Strom_regen_hex = map(Regen_off, 0, 438, 0x00, 0x7F);
  }
  Serial.write(byte(0x83));   //Regen Current Limit
  Serial.write(byte(Strom_regen_hex));

}
