#include "apps/globals.h"
#include "functions/reset_screen/reset.h"

uint16_t current_color = ST7735_CYAN; // default color is cyan
void open_color()
{
  current_page = 11; // color page
  rectangle_y_position = 10;
  tft.fillScreen(ST7735_BLACK);

  tft.setCursor(15, 15);
  tft.setTextColor(current_color);
  tft.print("blue");

  tft.setCursor(15, 35);
  tft.setTextColor(current_color);
  tft.print("green");

  tft.setCursor(15, 55);
  tft.setTextColor(current_color);
  tft.print("red");

  tft.setCursor(15, 75);
  tft.setTextColor(current_color);
  tft.print("white");

  tft.drawRect(10, rectangle_y_position, 70, 17, current_color);
}

void change_cyan()
{
    current_color = ST7735_CYAN;
}

void change_green()
{
    current_color = ST7735_GREEN;
}

void change_red()
{
    current_color = ST7735_RED;
}

void change_white()
{
    current_color = ST7735_WHITE;
}

int choose_color(int rectangle_y_position, int current_page)
{
    Serial.println("check color?");
    Serial.println(rectangle_y_position);
    Serial.println(current_page);
    if (rectangle_y_position == 10 && current_page == 11)
    {
        change_cyan();
        Serial.print("changed to cyan");
    } else if (rectangle_y_position == 30 && current_page == 11)
    {
        change_green();
        Serial.print("changed to green");
    } else if (rectangle_y_position == 50 && current_page == 11)
    {
        change_red();
        Serial.print("changed to red");
    } else if (rectangle_y_position == 70 && current_page == 11)
    {
        change_white();
        Serial.print("changed to white");
    }
    tft.setTextColor(current_color);
    reset_screen();
    return 0;
}