#include "apps/globals.h"
#include "secrets.h"
#include "functions/keyboard/keyboard.h"

extern int keyboard_x_position;
extern int keyboard_y_position;
extern int keyboard_row;
extern int letter_pos;

int calculate_number_position();
void save_calculation();
void clear_calculator();

int y = 98;
bool operator_choosen = false;
bool result_shown = false;

String num_operator;
String num_1;
String num_2;

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

  const int ROW2 = 3;   // row 2 starts at index 3
  const int ROW3 = 6;   // row 3 starts at index 6
  const int ROW4 = 9;   // row 4 starts at index 9

  for (int i = 0; i < 10; i++)
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

  tft.drawChar(50, 98,  '+', current_color, ST7735_BLACK, 1); // plus
  tft.drawChar(50, 108, '-', current_color, ST7735_BLACK, 1); // minus
  tft.drawChar(50, 118, '*', current_color, ST7735_BLACK, 1); // multiply
  tft.drawChar(68, 98,  '/', current_color, ST7735_BLACK, 1); // divide
  tft.drawChar(68, 108, 'C', current_color, ST7735_BLACK, 1); // clear
  tft.drawChar(68, 118, '=', current_color, ST7735_BLACK, 1); // equal
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
  } else if (keyboard_row == 4)
  {
    pos += 9;
  }

  if (pos < 0) pos = 0;
  if (pos > 9) pos = 9;

  return pos;
}

void clear_bar()
{
  tft.fillRect(0, 81, 160, 9, ST7735_BLACK);
}

void print_to_bar(String s)
{
  tft.setCursor(letter_pos += 5, 82);
  tft.print(s);
}

void show_result(String s)
{
  clear_bar();
  tft.setCursor(0, 82);
  tft.print(s);
  letter_pos = 5 * (int)s.length() - 5;
}

String format_result(double v)
{
  if (v == (long long)v) return String((long long)v);

  String s = String(v, 4);
  while (s.endsWith("0")) s.remove(s.length() - 1);
  if (s.endsWith(".")) s.remove(s.length() - 1);
  return s;
}

void save_calculation()
{
  calculation += calculator_characters[calculate_number_position()];
}


void evaluate()
{
  if (num_operator == "" || num_1 == "" || calculation == "") return;

  num_2 = calculation;

  double a = num_1.toDouble();
  double b = num_2.toDouble();
  double r = 0;

  if (num_operator == "+")
  {
    r = a + b;
  } else if (num_operator == "-")
  {
    r = a - b;
  } else if (num_operator == "*")
  {
    r = a * b;
  } else if (num_operator == "/")
  {
    if (b == 0)
    {
      show_result("ERR");
      num_1 = "";
      num_2 = "";
      num_operator = "";
      calculation = "";
      operator_choosen = false;
      result_shown = true;
      return;
    }
    r = a / b;
  }

  String out = format_result(r);
  show_result(out);

  calculation = out;
  num_1 = "";
  num_2 = "";
  num_operator = "";
  operator_choosen = false;
  result_shown = true;
}

void print_numbers()
{
  if (letter_pos >= 150) return; // max character limit

  bool right_column = (keyboard_x_position >= 66);
  bool op_column    = (keyboard_x_position >= 50);

  if (right_column && keyboard_y_position == 106)
  {
    clear_calculator();
    return;
  }

  if (right_column && keyboard_y_position == 117)
  {
    evaluate();
    return;
  }

  if (op_column)
  {
    if (operator_choosen) return;
    if (calculation == "") return;   // need a first number

    if (right_column && keyboard_y_position == 95)
    {
      num_operator = "/";
    } else if (keyboard_y_position == 95)
    {
      num_operator = "+";
    } else if (keyboard_y_position == 106)
    {
      num_operator = "-";
    } else if (keyboard_y_position == 117)
    {
      num_operator = "*";
    } else
    {
      return;
    }

    num_1 = calculation;
    calculation = "";
    operator_choosen = true;
    result_shown = false;

    print_to_bar(num_operator);
    return;
  }

  if (result_shown)
  {
    clear_calculator();
  }

  save_calculation();
  print_to_bar(calculator_characters[calculate_number_position()]);
}

void clear_calculator()
{
  clear_bar();
  operator_choosen = false;
  result_shown = false;
  letter_pos = -5;
  calculation = "";
  num_1 = "";
  num_2 = "";
  num_operator = "";
}