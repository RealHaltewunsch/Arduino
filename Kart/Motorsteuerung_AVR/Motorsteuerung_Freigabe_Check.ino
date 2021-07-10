void Freigabe_Check() {
  if (/*!Uebertemperatur && !Untertemperatur && !Temperatursensor_Fehler && */Gaspedal_angeschlossen /*&& Leistungselektronik*/) {
    Freigabe = true;
  }
  else {
    Freigabe = false;
  }
  digitalWrite(Freigabe_PIN_Leuchte, Freigabe);
}
