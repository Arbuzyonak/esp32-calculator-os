#include "apps/globals.h"

void open_main_page()
{
  rectangle_y_position = 10;
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(15, 15);
  tft.setTextColor(ST7735_CYAN);
  tft.print("Calculator");

  tft.setCursor(15, 35);
  tft.setTextColor(ST7735_CYAN);
  tft.print("Games");

  tft.setCursor(15, 55);
  tft.setTextColor(ST7735_CYAN);
  tft.print("Internet");

  tft.drawRect(10, rectangle_y_position, 70, 17, ST7735_CYAN);
}