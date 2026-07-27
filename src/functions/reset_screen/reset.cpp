#include "apps/globals.h"

extern void open_main_page();
extern int headline;
extern int keyboard_x_position;
extern int keyboard_y_position;
extern int keyboard_row;
extern int letter_pos;
extern String human_message;

void reset_screen()
{
    open_main_page();
    tft.setTextSize(1);
    current_page = 1;
    headline = 0;
    scroll = true;

    keyboard_x_position = 2;
    keyboard_y_position = 95;
    keyboard_row = 1;
    letter_pos = -5;
    human_message = "";
}