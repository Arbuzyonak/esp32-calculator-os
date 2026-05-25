#include "apps/globals.h"

void open_calculator_page()
{
  current_page = 2; // !!! Page 1 = Main page; Page 2 = Calculator; Page 3 = Games; Page 4 = Internet;
  rectangle_y_position = 10;
  tft.fillScreen(ST7735_BLACK);

  tft.setCursor(15, 15);
  tft.setTextColor(ST7735_CYAN);
  tft.print("Basic");

  tft.setCursor(15, 35);
  tft.setTextColor(ST7735_CYAN);
  tft.print("Converter");

  tft.setCursor(15, 55);
  tft.setTextColor(ST7735_CYAN);
  tft.print("Functions");

  tft.drawRect(10, rectangle_y_position, 70, 17, ST7735_CYAN);
}