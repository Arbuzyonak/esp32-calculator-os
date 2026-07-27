#include "apps/globals.h"
#include "secrets.h"
#include "functions/keyboard/keyboard.h"

extern int keyboard_x_position;
extern int keyboard_y_position;
extern int keyboard_row;

String calculator_characters[]
{
    "1", "2", "3",
    "4", "5", "6",
    "7", "8", "9",
         "0"
};

void initialize_calculator()
{
  current_page = 9;
  scroll = false;
  tft.fillScreen(ST7735_BLACK);

  int spacing = 16;
  int y = 98;

  const int ROW2 = 3;   // row 2 starts at index 3
  const int ROW3 = 6;   // row 3 starts at index 6
  const int ROW4 = 9;   // row 4 starts at index 9

  for (int i = 0; i < 9; i++)
  {
    if (i < ROW2)
      tft.setCursor(5 + i * spacing, y);
    else if (i < ROW3)
      tft.setCursor(5 + (i - ROW2) * spacing, y + 10);
    else if (i < ROW4)
      tft.setCursor(5 + (i - ROW3) * spacing, y + 20);
    else
      tft.setCursor(5 + (i - ROW4) * spacing, y + 30);

    tft.print(calculator_characters[i]);
  }

  tft.drawRect(keyboard_x_position, keyboard_y_position, 12, 12, ST7735_CYAN);
  tft.drawLine(0, 90, 160, 90, ST7735_CYAN);
  tft.drawLine(0, 80, 160, 80, ST7735_CYAN);
}