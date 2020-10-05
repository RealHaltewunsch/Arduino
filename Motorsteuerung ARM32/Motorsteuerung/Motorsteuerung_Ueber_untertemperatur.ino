void Ueber_Untertemperatur_auslesen() {
  if (MAX_TEMP_AKKU_RUN <= Max_Akku_Temperatur_erfragen() || MAX_TEMP_MOTOR <= Motor_Temperatur_erfragen() || MAX_TEMP_LEISTUNGSELEKTRONIK <= Max_Leistungselektronik_Temperatur_erfragen()) { //wenn True dann Überhitzt, erweitern um die anderen Sensoren
    Uebertemperatur_Zaehler++;
    if (Uebertemperatur_Zaehler >= Uebertemperatur_Zaehler_Speicher) {
      analogWrite(MOSFET_PIN, 0);
      Uebertemperatur = true;
    }
  }
  else if (MAX_TEMP_AKKU_STARTUP - 5 > Max_Akku_Temperatur_erfragen() && MAX_TEMP_MOTOR - 20 > Motor_Temperatur_erfragen () && MAX_TEMP_LEISTUNGSELEKTRONIK - 20 > Max_Leistungselektronik_Temperatur_erfragen()) { //wenn True dann um 10 bzw. 20 Grad runter gekühlt
    Uebertemperatur = false;
    Uebertemperatur_Zaehler = 0;
  }
  //ab hier wird die Untertemperatur ausgelesen
  if (Min_Akku_Temperatur_erfragen() <= MIN_TEMP_AKKU) {
    Untertemperatur_Zaehler++;
    if (Untertemperatur_Zaehler >= Untertemperatur_Zaehler_Speicher) {
      Untertemperatur = true;
    }
  }
  else if (Min_Akku_Temperatur_erfragen() > MIN_TEMP_AKKU) {
    Untertemperatur = false;
    Untertemperatur_Zaehler = 0;
  }
  //ab hier Temperatursensorfehler überprüfen
  if (Min_Akku_Temperatur_erfragen () <= 0 || Min_Leistungselektronik_Temperatur_erfragen () <= 0 || Motor_Temperatur_erfragen () <= 0) {
    Temperatursensor_Fehler_Zaehler++;
    if (Temperatursensor_Fehler_Zaehler >= Temperatursensor_Fehler_Zaehler_Speicher) {
      Temperatursensor_Fehler = true;
    }
  }
  else {
    Temperatursensor_Fehler = false;
    Temperatursensor_Fehler_Zaehler = 0;
  }

  Freigabe_Check(); //am Ende wird die Freigabe überprüft
}
