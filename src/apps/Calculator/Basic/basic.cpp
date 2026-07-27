#include "apps/globals.h"
#include "secrets.h"
#include "functions/keyboard/keyboard.h"

extern int keyboard_x_position;
extern int keyboard_y_position;
extern int keyboard_row;
extern int letter_pos;

int calculate_number_position();
void save_calculation();

String calculation;

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

  tft.drawRect(keyboard_x_position, keyboard_y_position, 12, 12, current_color);
  tft.drawLine(0, 90, 160, 90, current_color);
  tft.drawLine(0, 80, 160, 80, current_color); // borders

  tft.drawChar(50, 98, '+', current_color, ST7735_BLACK, 1); // plus
  tft.drawChar(50, 108, '-', current_color, ST7735_BLACK, 1); // minus
  tft.drawChar(50, 118, '*', current_color, ST7735_BLACK, 1); // multiply
  tft.drawChar(50, 128, '/', current_color, ST7735_BLACK, 1); // divide
}

int calculate_number_position()
{
  int pos = keyboard_x_position / 16;

  if (keyboard_row == 2)
  {
    pos += 3;
  } else if (keyboard_row == 3)
  {
    pos += 6;
  }

  return pos;
}

void print_numbers()
{
  if (letter_pos >= 150) return; // max character limit

  int c = calculate_number_position();
  tft.setCursor(letter_pos += 5, 82);
  tft.print(calculator_characters[c]);
  save_calculation();
}

void save_calculation()
{
  int c = calculate_number_position();

  if (letter_pos == 0)
  {
    calculation += calculator_characters[c];
  } else if (letter_pos >= 5)
  {
    calculation += calculator_characters[c];
    Serial.println(calculation);
  }
}

