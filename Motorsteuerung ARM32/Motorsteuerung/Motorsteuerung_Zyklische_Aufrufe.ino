void  Zyklische_Aufrufe() {
 
  /*
    if (currentMillis - previousMillis_Temperatur >= interval_Temperatur) {
    previousMillis_Temperatur = currentMillis;
    Temperaturen();
    }
  */

  if (currentMillis - previousMillis_Analog_Fehler >= interval_Analog_Fehler) {
    previousMillis_Analog_Fehler = currentMillis;
    AnalogSensor_Fehler();
  }
  
  if (currentMillis - previousMillis_OLED >= interval_OLED) {
    previousMillis_OLED = currentMillis;
    OLED_Display();
  }
  
  /*
  if (currentMillis - previousMillis_Batteriespannung >= interval_Batteriespannung) {
    previousMillis_Batteriespannung = currentMillis;

    SoftSerial.write((byte)0xCC);    //Supply Voltage lesen
    if (SoftSerial.available() > 0) {      //<-----------------------------------------------------------------------------------------------------möglicherweise Problematisch
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
  
  if (currentMillis - previousMillis_OLED_reset >= interval_OLED_reset) {
    previousMillis_OLED_reset = currentMillis;
    OLED_Reset = !OLED_Reset; //Variable wird geflippt, wenn das der Fall ist wird das von der OLED Fehler entfernen Funktion bearbeitet
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
