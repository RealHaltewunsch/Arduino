void OLED_Display () {
  Display_Fehler_entfernen();
  OLED_Display();
}

void Display_Fehler_entfernen() {
    else {  //damit werden die Konstanten nicht immer neu geschrieben
      ssd1306_setFixedFont(ssd1306xled_font5x7);  //5x7, 6x8
      ssd1306_printFixed(0,  0, "Temperaturen:", STYLE_NORMAL);   //(XX//YY)
      ssd1306_printFixed(0,  8, "Motor|Elektronik|Akku", STYLE_NORMAL);   //(XX//YY)
      ssd1306_printFixed(0,  24, "Bremse: " , STYLE_NORMAL);   //(XX//YY)
      ssd1306_printFixed(64,  24, "Zuendung: " , STYLE_NORMAL);   //(XX//YY)
      ssd1306_printFixed(0,  32, "Uebertemp: " , STYLE_NORMAL);   //(XX//YY)
      ssd1306_printFixed(64,  32, "Untertemp: " , STYLE_NORMAL);   //(XX//YY)
      ssd1306_printFixed(0,  40, "ASensFehl: " , STYLE_NORMAL);   //(XX//YY)
      ssd1306_printFixed(64,  40, "TSensFehl: " , STYLE_NORMAL);   //(XX//YY)
      ssd1306_printFixed(0,  48, "Gaspedal: " , STYLE_NORMAL);   //(XX//YY)
      ssd1306_printFixed(60,  48, "Regelung: " , STYLE_NORMAL);   //(XX//YY)
      //ssd1306_printFixed(40, 56, " V" , STYLE_NORMAL);   //(XX//YY)   //Fehler anfällig
      //ssd1306_printFixed(100, 56, " A" , STYLE_NORMAL);   //(XX//YY)  //Fehler anfällig
    }
  }
  


void OLED_Display() {
  char strOutputLine[25] = "";  //25
  char tempChar[40] = "";   //50
  char whitespace[] = "C     ";
  char Char[1];

  sprintf(tempChar, "%d", Temperatur_Motor);
  strcat (strOutputLine, tempChar);
  strcat (strOutputLine, whitespace);

  sprintf(tempChar, "%d", Temperatur_Leistungselektronik_Max);
  strcat (strOutputLine, tempChar);
  strcat (strOutputLine, whitespace);

  sprintf(tempChar, "%d", Temperatur_Akku_Max);
  strcat (strOutputLine, tempChar);

  ssd1306_setFixedFont(ssd1306xled_font5x7);  //5x7, 6x8
  ssd1306_printFixed(0,  0, "Temperaturen:", STYLE_NORMAL);   //(XX//YY)
  ssd1306_printFixed(0,  8, "Motor|Elektronik|Akku", STYLE_NORMAL);   //(XX//YY)
  ssd1306_printFixed(0,  16, strOutputLine , STYLE_NORMAL);   //(XX//YY)
  ssd1306_printFixed(0,  24, "Bremse: " , STYLE_NORMAL);   //(XX//YY)
  sprintf(Char, "%d", Bremse);  //Funktioniert
  ssd1306_printFixed(35,  24, Char , STYLE_NORMAL);   //(XX//YY)
  ssd1306_printFixed(64,  24, "Zuendung: " , STYLE_NORMAL);   //(XX//YY)
  sprintf(Char, "%d", Zuendung);  //Funktioniert
  ssd1306_printFixed(109,  24, Char , STYLE_NORMAL);   //(XX//YY)
  ssd1306_printFixed(0,  32, "Uebertemp: " , STYLE_NORMAL);   //(XX//YY)
  sprintf(Char, "%d", Uebertemperatur);  //Funktioniert
  ssd1306_printFixed(50,  32, Char , STYLE_NORMAL);   //(XX//YY)
  ssd1306_printFixed(64,  32, "Untertemp: " , STYLE_NORMAL);   //(XX//YY)
  sprintf(Char, "%d", Untertemperatur);  //Funktioniert
  ssd1306_printFixed(115,  32, Char , STYLE_NORMAL);   //(XX//YY)
  ssd1306_printFixed(0,  40, "ASensFehl: " , STYLE_NORMAL);   //(XX//YY)
  sprintf(Char, "%d", AnalogSensorFehler);  //Funktioniert
  ssd1306_printFixed(50,  40, Char , STYLE_NORMAL);   //(XX//YY)
  ssd1306_printFixed(64,  40, "TSensFehl: " , STYLE_NORMAL);   //(XX//YY)
  sprintf(Char, "%d", Temperatursensor_Fehler);  //Funktioniert
  ssd1306_printFixed(115,  40, Char , STYLE_NORMAL);   //(XX//YY)
  ssd1306_printFixed(0,  48, "Gaspedal: " , STYLE_NORMAL);   //(XX//YY)
  sprintf(Char, "%d", Gaspedal_angeschlossen);  //Funktioniert
  ssd1306_printFixed(50,  48, Char , STYLE_NORMAL);   //(XX//YY)
  ssd1306_printFixed(60,  48, "Reg_Brems " , STYLE_NORMAL);   //(XX//YY)
  sprintf(Char, "%d", Regenerativbremsen);  //Funktioniert
  ssd1306_printFixed(110,  48, Char , STYLE_NORMAL);   //(XX//YY)
  //ssd1306_printFixed(0, 56, Batteriespannung_char , STYLE_NORMAL);   //(XX//YY)
  //ssd1306_printFixed(20, 56, " V" , STYLE_NORMAL);   //(XX//YY)
  //ssd1306_printFixed(60, 56, Strom_char , STYLE_NORMAL);   //(XX//YY)
  //ssd1306_printFixed(50, 56, " A" , STYLE_NORMAL);   //(XX//YY)
}


/*
void OLED_Display_Freigabe() {

  char strOutputLine[25] = "";  //50
  char Geschwindigkeit_char[7];
  char tempChar[50] = "";
  char whitespace[] = "C     ";
  char Batteriespannung_char[5];
  //char LeistungChar[5];
  sprintf(tempChar, "%d", Temperatur_Motor);
  strcat (strOutputLine, tempChar);
  strcat (strOutputLine, whitespace);
  sprintf(tempChar, "%d", Temperatur_Leistungselektronik_Max);
  strcat (strOutputLine, tempChar);
  strcat (strOutputLine, whitespace);
  sprintf(tempChar, "%d", Temperatur_Akku_Max);
  strcat (strOutputLine, tempChar);

  dtostrf(Batteriespannung, 2, 1, Batteriespannung_char );    //für float
  // sprintf(LeistungChar, "%d", Leistung(Batteriespannung, Strom));

  sprintf(Geschwindigkeit_char, "%d", Geschwindigkeit_in_kmh);
  //dtostrf(Geschwindigkeit, 1, 1, Geschwindigkeit_char );    //für float
  strcat (Geschwindigkeit_char, " km/h");

  ssd1306_setFixedFont(ssd1306xled_font5x7);  //5x7, 6x8
  //ssd1306_printFixed(0,  0, "Temperaturen:", STYLE_NORMAL);   //(XX//YY)
  //ssd1306_printFixed(0,  8, "Motor|Elektronik|Akku", STYLE_NORMAL);   //(XX//YY)
  ssd1306_printFixed(0,  16, strOutputLine , STYLE_NORMAL);   //(XX//YY)
  ssd1306_printFixed(0,  30, Batteriespannung_char, STYLE_NORMAL);   //(XX//YY)
  //ssd1306_printFixed(20,  30, " V", STYLE_NORMAL);   //(XX//YY)
  //ssd1306_printFixed(55,  30, LeistungChar, STYLE_NORMAL);   //(XX//YY)
  //ssd1306_printFixed(70,  30, " W", STYLE_NORMAL);   //(XX//YY)

  ssd1306_setFixedFont(ssd1306xled_font8x16);
  ssd1306_printFixed2x(0,  36, Geschwindigkeit_char, STYLE_BOLD);
  ssd1306_setFixedFont(ssd1306xled_font5x7);  //5x7, 6x8
}

*/
