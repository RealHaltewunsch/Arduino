void Untertemperatur_auslesen() {
  if (Min_Akku_Temperatur_erfragen() <= MIN_TEMP_AKKU) {
    Untertemperatur_Zaehler++;
    if (Untertemperatur_Zaehler >= Untertemperatur_Zaehler_Speicher) {
      Untertemperatur = true;
    }
  }
  else if (Min_Akku_Temperatur_erfragen() > MIN_TEMP_AKKU) {
    Untertemperatur = false;
    Untertemperatur_Zaehler= 0;
  }
  Freigabe_Check();
}
