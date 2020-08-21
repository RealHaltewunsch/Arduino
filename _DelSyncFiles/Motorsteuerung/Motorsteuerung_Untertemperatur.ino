void Untertemperatur_auslesen() {
  if (Min_Akku_Temperatur_erfragen() <= MIN_TEMP_AKKU) {
    Untertemperatur = true;
  }
  else if (Min_Akku_Temperatur_erfragen() > MIN_TEMP_AKKU) {
    Untertemperatur = false;
  }
}
