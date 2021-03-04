void Initialwerte_schreiben () {
  Serial.write(byte(0xE0));   //UART Mode, wenn 3 Sekunden kein Update erfolgt, Shutdown!
  Serial.write(byte(0x8A));    //Direction
  Serial.write(byte(0x00));    // STOP
  Serial.write(byte(0x84)); //accel limit
  Serial.write(byte(0x00)); //min
  Serial.write(byte(0x85)); //decel limit
  Serial.write(byte(0x00)); //min
  Strom_hex = 0x00;
  Strom_regen_hex = 0x00;
  Strom_Rueckwaerts_hex = map(MAX_VALUE_CURRENT_RUECKWAERTS, 0, 434, 0x00, 0x7F);
  Schalter();
  Leistungselektronik_start = false;
}
