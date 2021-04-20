void Initialwerte_schreiben () {
  SEND(UART,0);
  SEND(DIR,STOP);
  Strom = 0;
  Strom_regen = 0;
  Strom_Rueckwaerts = map(MAX_VALUE_CURRENT_RUECKWAERTS, 0, 434, 0, 127);
  Schalter();
  Leistungselektronik_start = false;

}
