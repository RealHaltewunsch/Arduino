void  Gaspedal () {
  Sollwert_analog = Smooth_analog(A0, 5);
  Sollwert_analog = constrain (Sollwert_analog , 0, GASPEDAL_MAX);

  Beschleunigung_schreiben(Sollwert_analog, 0, Grenze_Gaspedal_empfindlich, Min_Acc_Delay, Max_Acc_Delay);
  Verzoegerung_schreiben(Sollwert_analog, 0, Grenze_Gaspedal_empfindlich, Min_Decc_Delay, Max_Decc_Delay,  Bremse);
  Geschwindigkeit_schreiben(Sollwert_analog, Gang_wechseln, Bremse);
 
}

void Gaspedal_check () {
  Gaspedal_angeschlossen = !digitalRead(Gaspedal_check_PIN); //Gaspedal Pin low wenn angeschlossen
  Freigabe_Check();
}

int Smooth_analog (int analog, int cycles) {
  long unsigned int Sollwert_intern  = 0;
  for (int i = 0; i <= cycles; i++) {
    Sollwert_intern =  analogRead(analog) + Sollwert_intern;
  }
  Sollwert_intern = Sollwert_intern / cycles;
  return Sollwert_intern;
}

void Beschleunigung_schreiben (unsigned short int Pedal, unsigned short int Grenze_unten, unsigned short int Grenze_oben, unsigned short int Min_delay, unsigned short int Max_delay) {
  Beschleunigungslimit_alt = Beschleunigungslimit;
  if (Pedal >= Grenze_unten && Pedal <= Grenze_oben) {
    Beschleunigungslimit = map (Pedal, Grenze_unten, Grenze_oben, Max_delay, Min_delay); //Wenn Pedal = Grenze_grenze oben, ist minimaler Beschleunigungsdelay
  }
  else if (Pedal > Grenze_oben) {
    Beschleunigungslimit = Min_delay;
  }
  else {
    Beschleunigungslimit = Max_delay;
  }
  if (Beschleunigungslimit_alt != Beschleunigungslimit) {
    SEND(ACC, Beschleunigungslimit);
  }
}

void Verzoegerung_schreiben (unsigned short int Pedal, unsigned short int Grenze_unten, unsigned short int Grenze_oben, unsigned short int Min_delay, unsigned short int Max_delay , bool Bremse_read) {
  unsigned short int Verzoegerungslimit_alt = Verzoegerungslimit;
  if (Bremse_read || Pedal < GASPEDAL_MIN) {
    Verzoegerungslimit = 0;
  }
  else if (Pedal >= Grenze_unten && Pedal <= Grenze_oben) {
    Verzoegerungslimit = map (Pedal, Grenze_unten, Grenze_oben, Max_delay, Min_delay);  //
  }
  else if (Pedal > Grenze_oben) {
    Verzoegerungslimit = Min_delay;
  }
  else {
    Verzoegerungslimit = 0;
  }
  if (Verzoegerungslimit_alt != Verzoegerungslimit) {
    SEND(DECC, Verzoegerungslimit);
  }
}


void Geschwindigkeit_schreiben (unsigned short int Pedal, bool Gang_wechseln_read, bool Bremse_read) {
  if (Pedal > GASPEDAL_MIN && !Gang_wechseln_read && !Bremse_read) {
    Sollwert = map (Pedal, GASPEDAL_MIN, GASPEDAL_MAX, 0, 127);
    previousMillis_Inaktiv = currentMillis;
  }
  else {
    Sollwert = 0;
  }
  SEND(SPEED, Sollwert);
}