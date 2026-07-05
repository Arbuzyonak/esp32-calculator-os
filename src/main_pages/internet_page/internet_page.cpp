#include "apps/globals.h"

void open_internet_page()
{
  current_page = 4;
  rectangle_y_position = 10;
  tft.fillScreen(ST7735_BLACK);

  tft.setCursor(15, 15);
  tft.setTextColor(ST7735_CYAN);
  tft.print("Weather");

  tft.setCursor(15, 35);
  tft.setTextColor(ST7735_CYAN);
  tft.print("Clock ");

  tft.setCursor(15, 55);
  tft.setTextColor(ST7735_CYAN);
  tft.print("News");

  tft.setCursor(15, 75);
  tft.setTextColor(ST7735_CYAN);
  tft.print("Groq");

  tft.setCursor(15, 95);
  tft.setTextColor(ST7735_CYAN);
  tft.print("Home Server");

  tft.drawRect(10, rectangle_y_position, 70, 17, ST7735_CYAN);
}