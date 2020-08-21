#include "ssd1306.h"
//#include "ssd1306_console.h"
//STM32: B7(SDA), B6(SCL)
//Ssd1306Console  console;

volatile int Geschwindigkeit = 0;

volatile int Temp1 = 30;
volatile int Temp2 = 20;
volatile int Temp3 = 25;

volatile bool Freigabe = false;
bool Freigabe_alt;
volatile bool Freigabe_neu;
bool Geschwindigkeit_gross_alt; //verwirrendes Konzept, aber das wird benötigt, da sonst ein Anzeigefehler ensteht wenn man von einer einstellingen Geschwindigkeit zu einer zweistelligen Geschwindigkeit wechselt
bool Geschwindigkeit_gross; //verwirrendes Konzept, aber das wird benötigt, da sonst ein Anzeigefehler ensteht wenn man von einer einstellingen Geschwindigkeit zu einer zweistelligen Geschwindigkeit wechselt
bool Geschwindigkeit_Vorzeichen_alt; //verwirrendes Konzept, aber das wird benötigt, da sonst ein Anzeigefehler ensteht wenn man von negativ zu positiv wechselt...
bool Geschwindigkeit_Vorzeichen;  //verwirrendes Konzept, aber das wird benötigt, da sonst ein Anzeigefehler ensteht wenn man von negativ zu positiv wechselt...

volatile bool Bremse, Zuendung, Uebertemperatur, Untertemperatur, AnalogSensorFehler, Temperatursensor_Fehler , Gaspedal_angeschlossen;




void setup() {
  ssd1306_128x64_i2c_init();
  pinMode(PA0, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(PA0), Freigabe_wechseln, RISING);
  ssd1306_clearScreen();


}

void loop() {

  OLED_Display();


}

void Display_Fehler_entfernen() {
  Geschwindigkeit_gross_alt = Geschwindigkeit_gross;
  if (Geschwindigkeit >= 10 || Geschwindigkeit <= -10) {
    Geschwindigkeit_gross = true;
  }
  else {
    Geschwindigkeit_gross = false;
  }
  Geschwindigkeit_Vorzeichen_alt = Geschwindigkeit_Vorzeichen;
  if (Geschwindigkeit < 0) {
    Geschwindigkeit_Vorzeichen = true;
  }
  else {
    Geschwindigkeit_Vorzeichen = false;
  }
  if (Freigabe_alt != Freigabe || Geschwindigkeit_gross_alt != Geschwindigkeit_gross || Geschwindigkeit_Vorzeichen_alt != Geschwindigkeit_Vorzeichen) { //sonst werden komisches Sachen angezeigt...
    ssd1306_clearScreen();    //hier rum gehts, das wird so komisch implementiert da sonst immer der gesamte Bildschirm flackert und das nervt!
  }
  Freigabe_alt = Freigabe;
}

void OLED_Display () {
  Display_Fehler_entfernen();
  if (Freigabe) {
    OLED_Display_Freigabe();
  }
  else {
    OLED_Display_Fehler();
  }
}

void Freigabe_wechseln () {
  Freigabe = !Freigabe;
  Temp1++;
  Temp2++;
  Temp3++;
  Bremse = !Bremse;
  Zuendung = !Zuendung;
  Uebertemperatur = !Uebertemperatur;
  Untertemperatur = !Untertemperatur;
  AnalogSensorFehler = !AnalogSensorFehler;
  Temperatursensor_Fehler = !Temperatursensor_Fehler;
  Gaspedal_angeschlossen = !Gaspedal_angeschlossen;
}

void OLED_Display_Fehler() {
  char strOutputLine[50] = "";
  char tempChar[50] = "";
  char whitespace[] = "C      ";


  char BremseChar[1];
  sprintf(BremseChar, "%d", Bremse);  //Funktioniert
  char ZuendungChar[1];
  sprintf(ZuendungChar, "%d", Zuendung);  //Funktioniert
  char UebertemperaturChar[1];
  sprintf(UebertemperaturChar, "%d", Uebertemperatur);  //Funktioniert
  char UntertemperaturChar[1];
  sprintf(UntertemperaturChar, "%d", Untertemperatur);  //Funktioniert
  char AnalogSensorFehlerChar[1];
  sprintf(AnalogSensorFehlerChar, "%d", AnalogSensorFehler);  //Funktioniert
  char Temperatursensor_FehlerChar[1];
  sprintf(Temperatursensor_FehlerChar, "%d", Temperatursensor_Fehler);  //Funktioniert
  char Gaspedal_angeschlossenChar[1];
  sprintf(Gaspedal_angeschlossenChar, "%d", Gaspedal_angeschlossen);  //Funktioniert

  sprintf(tempChar, "%d", Temp1);
  strcat (strOutputLine, tempChar);
  strcat (strOutputLine, whitespace);

  sprintf(tempChar, "%d", Temp2);
  strcat (strOutputLine, tempChar);
  strcat (strOutputLine, whitespace);

  sprintf(tempChar, "%d", Temp3);
  strcat (strOutputLine, tempChar);
  strcat (strOutputLine, whitespace);
  ssd1306_setFixedFont(ssd1306xled_font5x7);  //5x7, 6x8
  ssd1306_printFixed(0,  0, "Temperaturen:", STYLE_NORMAL);   //(XX//YY)
  ssd1306_printFixed(0,  8, "Motor|Elektronik|Akku", STYLE_NORMAL);   //(XX//YY)
  ssd1306_printFixed(0,  16, strOutputLine , STYLE_NORMAL);   //(XX//YY)
  ssd1306_printFixed(0,  24, "Bremse: " , STYLE_NORMAL);   //(XX//YY)
  ssd1306_printFixed(35,  24, BremseChar , STYLE_NORMAL);   //(XX//YY)
  ssd1306_printFixed(64,  24, "Zuendung: " , STYLE_NORMAL);   //(XX//YY)
  ssd1306_printFixed(109,  24, ZuendungChar , STYLE_NORMAL);   //(XX//YY)
  ssd1306_printFixed(0,  32, "Uebertemp: " , STYLE_NORMAL);   //(XX//YY)
  ssd1306_printFixed(50,  32, UebertemperaturChar , STYLE_NORMAL);   //(XX//YY)
  ssd1306_printFixed(64,  32, "Untertemp: " , STYLE_NORMAL);   //(XX//YY)
  ssd1306_printFixed(115,  32, UntertemperaturChar , STYLE_NORMAL);   //(XX//YY)
  ssd1306_printFixed(0,  40, "ASensFehl: " , STYLE_NORMAL);   //(XX//YY)
  ssd1306_printFixed(50,  40, AnalogSensorFehlerChar , STYLE_NORMAL);   //(XX//YY)
  ssd1306_printFixed(64,  40, "TSensFehl: " , STYLE_NORMAL);   //(XX//YY)
  ssd1306_printFixed(115,  40, Temperatursensor_FehlerChar , STYLE_NORMAL);   //(XX//YY)
  ssd1306_printFixed(0,  48, "Gaspedal Fehler: " , STYLE_NORMAL);   //(XX//YY)
  ssd1306_printFixed(80,  48, Gaspedal_angeschlossenChar , STYLE_NORMAL);   //(XX//YY)


}

void OLED_Display_Freigabe() {

  char strOutputLine[50] = "";
  char Geschwindigkeit_char[7];
  char tempChar[50] = "";
  char whitespace[] = "C      ";
  sprintf(tempChar, "%d", Temp1);
  strcat (strOutputLine, tempChar);
  strcat (strOutputLine, whitespace);
  sprintf(tempChar, "%d", Temp2);
  strcat (strOutputLine, tempChar);
  strcat (strOutputLine, whitespace);
  sprintf(tempChar, "%d", Temp3);
  strcat (strOutputLine, tempChar);
  strcat (strOutputLine, whitespace);

  sprintf(Geschwindigkeit_char, "%d", Geschwindigkeit);
  //dtostrf(Geschwindigkeit, 1, 1, Geschwindigkeit_char );    //für float
  strcat (Geschwindigkeit_char, " km/h");
  ssd1306_setFixedFont(ssd1306xled_font5x7);  //5x7, 6x8
  ssd1306_printFixed(0,  0, "Temperaturen:", STYLE_NORMAL);   //(XX//YY)
  ssd1306_printFixed(0,  8, "Motor|Elektronik|Akku", STYLE_NORMAL);   //(XX//YY)
  ssd1306_printFixed(0,  16, strOutputLine , STYLE_NORMAL);   //(XX//YY)
  ssd1306_setFixedFont(ssd1306xled_font5x7);
  ssd1306_printFixed(25,  30, "Geschwindigkeit", STYLE_BOLD);   //(XX//YY)
  ssd1306_setFixedFont(ssd1306xled_font8x16);
  ssd1306_printFixed2x(0,  38, Geschwindigkeit_char, STYLE_BOLD);

}
