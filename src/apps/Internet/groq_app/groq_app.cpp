#include "apps/globals.h"
extern int initialize_keyboard();

void open_ai() {
  current_page = 8;
  scroll = false;

  tft.fillScreen(ST7735_BLACK);

  initialize_keyboard();
}