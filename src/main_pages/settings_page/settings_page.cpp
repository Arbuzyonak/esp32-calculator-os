#include "apps/globals.h"

void open_settings_page()
{
    tft.fillScreen(ST7735_BLACK);
    current_page = 10;
    rectangle_y_position = 10;

    tft.setCursor(15, 15);
    tft.setTextColor(current_color);
    tft.print("wifi");

    tft.setCursor(15, 35);
    tft.setTextColor(current_color);
    tft.print("colour ");

    tft.drawRect(10, rectangle_y_position, 70, 17, current_color);
}