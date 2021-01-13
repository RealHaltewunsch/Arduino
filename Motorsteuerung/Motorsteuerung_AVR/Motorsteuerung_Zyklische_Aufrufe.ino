void  Zyklische_Aufrufe() {
/*
  if (currentMillis - previousMillis_Temperatur >= interval_Temperatur) {
    previousMillis_Temperatur = currentMillis;
    Temperaturen();
  }
*/
  if (currentMillis - previousMillis_Schalter >= interval_Schalter) {
    previousMillis_Schalter = currentMillis;
    Schalter();
  }


  if (currentMillis - previousMillis_Analog_Fehler >= interval_Analog_Fehler) {
    previousMillis_Analog_Fehler = currentMillis;
    AnalogSensor_Fehler();
  }

  if (currentMillis - previousMillis_OLED >= interval_OLED) {
    previousMillis_OLED = currentMillis;
    OLED_Display();
    display.display();
  }


  /*
    if (currentMillis - previousMillis_Batteriespannung >= interval_Batteriespannung) {
    previousMillis_Batteriespannung = currentMillis;

    Serial.write((byte(0xCC));    //Supply Voltage lesen
    if (Serial.available() > 0) {      //<-----------------------------------------------------------------------------------------------------möglicherweise Problematisch
      Batteriespannung_hex = Serial.read();
      Batteriespannung = map(Batteriespannung_hex,0x00,0x7F,0,156);
    }
    }
  */

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
