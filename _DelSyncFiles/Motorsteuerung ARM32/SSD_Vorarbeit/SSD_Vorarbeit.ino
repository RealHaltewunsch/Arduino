#include "ssd1306.h"
#include "ssd1306_console.h"
//STM32: B7(SDA), B6(SCL)
//Ssd1306Console  console;

int Geschwindigkeit = 102;

int Temp1 = 30;
int Temp2 = 20;
int Temp3 = 25;

void setup() {
  ssd1306_128x64_i2c_init();
  ssd1306_setFixedFont(ssd1306xled_font6x8);
  ssd1306_clearScreen();
}

void loop() {
  OLED_Display();
}

void OLED_Display() {

  char strOutputLine[50] = "";
  char Geschwindigkeit_char[7];
  char tempChar[50] = "";
  char whitespace[] = "C        ";

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

  //ssd1306_clearScreen();
  ssd1306_setFixedFont(ssd1306xled_font5x7);  //5x7, 6x8
  ssd1306_printFixed(0,  0, "Temperaturen:", STYLE_NORMAL);   //(XX//YY)
  ssd1306_printFixed(0,  10, "Motor|Elektronik|Akku", STYLE_NORMAL);   //(XX//YY)
  ssd1306_printFixed(0,  20, strOutputLine , STYLE_NORMAL);   //(XX//YY)
  ssd1306_setFixedFont(ssd1306xled_font5x7);
  ssd1306_printFixed(25,  30, "Geschwindigkeit", STYLE_BOLD);   //(XX//YY)
  ssd1306_setFixedFont(ssd1306xled_font8x16);
  ssd1306_printFixed2x(0,  38, Geschwindigkeit_char, STYLE_BOLD);
}
