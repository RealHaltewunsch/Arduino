void  Zyklische_Aufrufe() {

  if (currentMillis - previousMillis_Temperatur >= interval_Temperatur) {
    previousMillis_Temperatur = currentMillis;
    Temperaturen();
  }

  if (currentMillis - previousMillis_Schalter >= interval_Schalter) {
    previousMillis_Schalter = currentMillis;
    Schalter();
  }

  /*if (Neutral && currentMillis - previousMillis_Batteriespannung >= interval_Batteriespannung) {
    flushReceive();
    SEND(VOLT, 0);
    int Spannung_internal = 0;
    previousMillis_Batteriespannung = currentMillis;
    if (Serial.available() > 0) {
      Spannung_internal = Serial.read();
    }
    Spannung_internal = constrain (Spannung_internal, 0, 127);
    Batteriespannung = map (Spannung_internal, 0, 127, 0 , 156);
    if (Batteriespannung >= 60) {
      SOC = map(Batteriespannung, 60 , 80, 0 , 100);
    }
    else {
      SOC = 0;
    }
    //pixels.clear();
    int Red = map(SOC, 0, 100, 255, 0);
    int Green = map(SOC, 0, 100, 0, 255);

    for (int i = 0; i < map(SOC, 0, 100, 1, NUMPIXELS); i++) { // For each pixel...

      //pixels.setPixelColor(i, pixels.Color(Red, Green, 0));
    }
    //pixels.show();   // Send the updated pixel colors to the hardware.
    }
  */

  if (Neutral && currentMillis - previousMillis_Rueckwaerts_LED >= interval_Rueckwaerts_LED_LED) {
    previousMillis_Rueckwaerts_LED = currentMillis;
    Rueckwaerts_LED = !Rueckwaerts_LED;
    digitalWrite(Rueckwaerts_PIN_Leuchte, Rueckwaerts_LED);
  }

  if (currentMillis - previousMillis_Rueckwaerts >= interval_Rueckwaerts) {
    previousMillis_Rueckwaerts = currentMillis;
    Rueckwaerts_auslesen();
  }
  /*
    if (currentMillis - previousMillis_OLED >= interval_OLED) {
      previousMillis_OLED = currentMillis;
      OLED_Display();
      display.display();
    }
  */

  if (currentMillis - previousMillis_Inaktiv >= interval_Inaktiv && !Inaktiv) {
    Neutral = true;
    Gang_wechseln = true;
    Inaktiv = true;
  }
  else {
    Inaktiv = false;
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
