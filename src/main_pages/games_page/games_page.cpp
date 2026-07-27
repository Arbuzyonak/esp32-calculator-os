#include "apps/globals.h"

void open_games_page()
{
  current_page = 3;
  rectangle_y_position = 10;
  tft.fillScreen(ST7735_BLACK);

  tft.setCursor(15, 15);
  tft.setTextColor(current_color);
  tft.print("Snake");

  tft.setCursor(15, 35);
  tft.setTextColor(current_color);
  tft.print("Pong");

  tft.setCursor(15, 55);
  tft.setTextColor(current_color);
  tft.print("X&O");

  tft.setCursor(15, 75);
  tft.setTextColor(current_color);
  tft.print("Reaction");

  tft.setCursor(15, 95);
  tft.setTextColor(current_color);
  tft.print("Number");

  tft.drawRect(10, rectangle_y_position, 70, 17, current_color);
}