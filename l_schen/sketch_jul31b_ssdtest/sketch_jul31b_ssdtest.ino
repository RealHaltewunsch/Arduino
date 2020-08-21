#include "ssd1306.h"
#include "nano_gfx.h"
//STM32: B7(SDA), B6(SCL)

void setup() {
  // put your setup code here, to run once:
  ssd1306_setFixedFont(ssd1306xled_font6x8);
  ssd1306_128x64_i2c_init();
  ssd1306_clearScreen();
  test();
  test2();
}

void loop() {
  // put your main code here, to run repeatedly:
  //test();
}

void test() {
  ssd1306_print("test was passiert hier");
}
void test2() {
  ssd1306_setFixedFont(ssd1306xled_font8x16);
  ssd1306_print(" groß test was passiert hier");
}





static void textDemo()
{
  ssd1306_setFixedFont(ssd1306xled_font6x8);
  ssd1306_clearScreen();
  ssd1306_printFixed(0,  8, "Normal text", STYLE_NORMAL);
  ssd1306_printFixed(0, 16, "Bold text", STYLE_BOLD);
  ssd1306_printFixed(0, 24, "Italic text", STYLE_ITALIC);
  ssd1306_negativeMode();
  ssd1306_printFixed(0, 32, "Inverted bold", STYLE_BOLD);
  ssd1306_positiveMode();
  delay(3000);
}
