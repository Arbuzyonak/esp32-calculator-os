#include "apps/globals.h"

void open_main_page()
{
  rectangle_y_position = 10;
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(15, 15);
  tft.setTextColor(current_color);
  tft.print("Calculator");

  tft.setCursor(15, 35);
  tft.setTextColor(current_color);
  tft.print("Games");

  tft.setCursor(15, 55);
  tft.setTextColor(current_color);
  tft.print("Internet");

  tft.setCursor(15, 75);
  tft.setTextColor(current_color);
  tft.print("Settings");

  tft.drawRect(10, rectangle_y_position, 70, 17, current_color);
}