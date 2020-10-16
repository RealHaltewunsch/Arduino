void Temperatur_LED_blinken() {
  if (currentMillis - previousMillis_Temperatur_LED >= interval_Temperatur_LED) {
    previousMillis_Temperatur_LED = currentMillis;
    Temperatur_LED_Zustand = !Temperatur_LED_Zustand;
    digitalWrite(Uebertemperatur_PIN_Leuchte, Temperatur_LED_Zustand);
  }
}

void Temperatursensor_Fehler_LED_blinken() {
  if (currentMillis - previousMillis_Temperatursensor_Fehler_LED >= interval_Temperatursensor_Fehler_LED) {
    previousMillis_Temperatursensor_Fehler_LED = currentMillis;
    Temperatursensor_Fehler_LED_Zustand = !Temperatursensor_Fehler_LED_Zustand;
    digitalWrite(Uebertemperatur_PIN_Leuchte, Temperatursensor_Fehler_LED_Zustand);
  }
}
