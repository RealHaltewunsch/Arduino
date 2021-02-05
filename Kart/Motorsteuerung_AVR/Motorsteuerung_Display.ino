//http://oleddisplay.squix.ch/#/home

void OLED_Display() {
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setFont(&Dialog_plain_9);
  display.setCursor(0, 7);
  display.println("Motor|Elektronik|Akku");
  display.setFont(&Dialog_plain_7);
  display.setCursor(0, 13);
  display.print(Temperatur_Motor);
  display.print("C | ");
  display.print(Temperatur_Leistungselektronik);
  display.print("C | ");
  display.print(Temperatur_Akku_Max);
  display.print("C");
  display.setCursor(0, 19);
  display.print("Bremse: ");
  display.print(Bremse);
  display.print("  ");
  display.print("Gaspedal: ");
  display.print(Gaspedal_angeschlossen);
  display.print("h");
  display.print(Sollwert_hex);
  display.setCursor(0, 25);
  display.print("TSensFehl: ");
  display.print(Temperatursensor_Fehler);
  display.print("  ");
  display.print("Uebertemp: ");
  display.print(Uebertemperatur);
  display.setCursor(0, 31);
  display.print("Untertemp: ");
  display.print(Untertemperatur);
  display.print("  ");
  display.print("ASensFehl: ");
  display.print(AnalogSensorFehler);





}
