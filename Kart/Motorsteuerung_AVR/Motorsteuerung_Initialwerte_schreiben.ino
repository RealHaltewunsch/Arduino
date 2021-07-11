void Initialwerte_schreiben () {
  Serial.begin(9600);  //Kommunikation mit Leistungselektronik
  Serial.setTimeout(250);
  SEND(UART, 0);
  SEND(DIR, STOP);
  SEND(ACC, 0);
  SEND(DECC, 0);
  Strom = 0;
  Strom_regen = 0;
  Strom_Rueckwaerts = map(MAX_VALUE_CURRENT_RUECKWAERTS, 0, 434, 0, 127);
  Regen_off = map(REGEN_OFF, 0, 434, 0, 127);
  Regen_on = map(REGEN_ON, 0, 434, 0, 127);
  Regen_on_Sport = map(REGEN_ON_SPORT, 0, 434, 0, 127);
  Schalter();
  Leistungselektronik_start = false;
  Delay_berechnen ();
}


void Delay_berechnen () {
  Grenze_Gaspedal_empfindlich_Sport = map(GRENZE_GASPEDAL_EMPFINDLICH_SPORT, 0, 100, 0, 127);
  Max_Ac_Delay_Sport = map(MAX_ACC_DELAY_SPORT, 0, 100, 0, 127);
  Min_Ac_Delay_Sport = map(MIN_ACC_DELAY_SPORT, 0, 100, 0, 127);
  Max_Dec_Delay_Sport = map(MAX_DECC_DELAY_SPORT, 0, 100, 0, 127);
  Min_Dec_Delay_Sport = map(MIN_DECC_DELAY_SPORT, 0, 100, 0, 127);

  Grenze_Gaspedal_empfindlich = map(GRENZE_GASPEDAL_EMPFINDLICH, 0, 100, 0, 127);
  Max_Ac_Delay = map(MAX_ACC_DELAY, 0, 100, 0, 127);
  Min_Ac_Delay = map(MIN_ACC_DELAY, 0, 100, 0, 127);
  Max_Dec_Delay = map(MAX_DECC_DELAY, 0, 100, 0, 127);
  Min_Dec_Delay = map(MIN_DECC_DELAY, 0, 100, 0, 127);
}
