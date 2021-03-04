void  Zyklische_Aufrufe() {

  if (currentMillis - previousMillis_Temperatur >= interval_Temperatur) {
    previousMillis_Temperatur = currentMillis;
    Temperaturen();
  }

  if (currentMillis - previousMillis_Schalter >= interval_Schalter) {
    previousMillis_Schalter = currentMillis;
    Schalter();
  }


  if (currentMillis - previousMillis_Analog_Fehler >= interval_Analog_Fehler) {
    previousMillis_Analog_Fehler = currentMillis;
    AnalogSensor_Fehler();
  }

  if (Neutral && currentMillis - previousMillis_Rueckwaerts >= interval_Rueckwaerts) {
    previousMillis_Rueckwaerts = currentMillis;
    Rueckwaerts_LED = !Rueckwaerts_LED;
    digitalWrite(Rueckwaerts_PIN_Leuchte, Rueckwaerts_LED);
  }

  /*
    if (currentMillis - previousMillis_OLED >= interval_OLED) {
      previousMillis_OLED = currentMillis;
      OLED_Display();
      display.display();
    }
  */

  if (currentMillis - previousMillis_Inaktiv >= interval_Inaktiv) {
    previousMillis_Inaktiv = currentMillis;
    Neutral = true;
    Gang_wechseln = true;
  }

  if (currentMillis - previousMillis_LED >= interval_LED) {
    previousMillis_LED = currentMillis;
    TestLED = !TestLED;
    digitalWrite(TestLED_PIN, TestLED);
  }

  if (Uebertemperatur) {
    digitalWrite(Uebertemperatur_PIN_Leuchte, HIGH);
  }
  else if (Untertemperatur) {
    Temperatur_LED_blinken(); //LED blinkt schnell
  }
  else if (Temperatursensor_Fehler) {
    Temperatursensor_Fehler_LED_blinken();    //LED blinkt langsam
  }
  else {
    digitalWrite(Uebertemperatur_PIN_Leuchte, LOW);
  }
}
