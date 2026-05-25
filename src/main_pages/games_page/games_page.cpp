#include "apps/globals.h"

void open_games_page()
{
  current_page = 3;
  rectangle_y_position = 10;
  tft.fillScreen(ST7735_BLACK);

  tft.setCursor(15, 15);
  tft.setTextColor(ST7735_CYAN);
  tft.print("Snake");

  tft.setCursor(15, 35);
  tft.setTextColor(ST7735_CYAN);
  tft.print("Pong");

  tft.setCursor(15, 55);
  tft.setTextColor(ST7735_CYAN);
  tft.print("X&O");

  tft.setCursor(15, 75);
  tft.setTextColor(ST7735_CYAN);
  tft.print("Reaction");

  tft.setCursor(15, 95);
  tft.setTextColor(ST7735_CYAN);
  tft.print("Number");

  tft.drawRect(10, rectangle_y_position, 70, 17, ST7735_CYAN);
}