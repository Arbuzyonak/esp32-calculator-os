#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#include "apps/Internet/weather_app/weather_app.h"
#include "apps/Internet/news_app/news_app.h"
#include "apps/Internet/clock_app/clock_app.h"
#include "apps/Internet/gemeni_app/gemeni_app.h"

#include "main_pages/internet_page/internet_page.h"
#include "main_pages/games_page/games_page.h"
#include "main_pages/calculator_page/calculator_page.h"
#include "main_pages/main_page/main_page.h"

#include "secrets.h"

// Notes: use canvaces instead of directly printing // Instead of buttons use http and a browser for now

const char *ssid = WIFI_SSID;
const char *password = WIFI_PASSWORD;

// tft object variables
const int TFT_CS = 5;
const int TFT_DC = 4;
const int TFT_RST = 2;

// button variables
const int up_button = 34;
const int down_button = 17;
const int left_button = 13;
const int right_button = 12;
const int select_button = 19;

const int CLK = 35;
const int DT = 32;
const int SW = 33; // Change all of these numbers cuz they aint workin

int counter = 0;
int currentStateCLK;
int lastStateCLK;

int rectangle_y_position = 10;

int keyboard_x_position = 2; // 146
int keyboard_y_position = 95; // 95, 105, 115
int keyboard_row = 1;

String letters[] = {
    "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P",
    "A", "S", "D", "F", "G", "H", "J", "K", "L",
    "Z", "X", "C", "V", "B", "N", "M"
  };

int current_page = 1;

int headline = 0;
int letter_pos = -5;

bool scroll = true;

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void initialize_screen();  // Start up screen
void initialize_buttons(); // pinMode setup
void initialize_loading();
void initialize_keyboard();

void move_up_rectangle();   // Move the select rectangle 20 pixels up
void move_down_rectangle(); // Move the select rectangle 20 pixels down

void move_keyboard_right();
void move_keyboard_left();
void move_keyboard_up();
void move_keyboard_down();
int calculate_letter_position();

void open_main_page();       // Draw the main screen the Calculator, Games and Internet buttons
void open_calculator_page(); // Open the page with all the functions for math
void open_games_page();      // Open the page with all the games
void open_internet_page();   // Open the page with all the internet apps

void open_weather_app();   // Get weather data for Montreal
void open_weather_app_2(); // second page of the weather app
void open_clock_app();     // Open the clock app

void open_news_app(); // Open the news app
void open_general_news(int position);

void open_gemeni();

void setup()
{
  Serial.begin(115200);
  initialize_screen();
  initialize_buttons();

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected!");
  Serial.println(WiFi.localIP());
  Serial.println(WiFi.dnsIP());

  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
  pinMode(SW, PULLUP);
}

void loop()
{
  {
    if (digitalRead(up_button) == HIGH && digitalRead(down_button) == HIGH)
    { // Go to the main page from the calcualtor page
      if (current_page == 1)
        return;

      open_main_page();
      tft.setTextSize(1);
      current_page = 1;
      headline = 0;
      scroll = true;
      
      keyboard_x_position = 2;
      keyboard_y_position = 95;
      keyboard_row = 1;
      letter_pos = -5;
    }

    if (digitalRead(up_button) == HIGH)
    { // go up

      if (current_page == 8) {
        move_keyboard_up();
      }

      if (scroll == false) return;
      if (rectangle_y_position == 10) return;
      move_up_rectangle();
    }

    if (digitalRead(down_button) == HIGH)
    { // go down
      
      if (current_page == 8) {
        move_keyboard_down();
        delay(200);
      }

      if (scroll == false)
        return;

      if (rectangle_y_position >= 50 && !(current_page == 3 || current_page == 4 || current_page == 7))
        return;
      if (rectangle_y_position >= 90 && (current_page == 3 || current_page == 4))
        return;
      if (rectangle_y_position >= 110 && (current_page == (7)))
        return;
      move_down_rectangle();
    }

    if (digitalRead(right_button) == HIGH) {
      if (current_page == 8) move_keyboard_right();
    }

    if (digitalRead(left_button) == HIGH) {
      if (current_page == 8) move_keyboard_left();
    }

    if (digitalRead(select_button) == HIGH)
    { // The options are divided like this: Calculator = 10p; Games = 30p; Internet = 50p;
      if (rectangle_y_position == 10 && current_page == 1)
      {
        open_calculator_page();
      }
      else if (rectangle_y_position == 30 && current_page == 1)
      {
        open_games_page();
      }
      else if (rectangle_y_position == 50 && current_page == 1)
      {
        open_internet_page();
      }
      else if (rectangle_y_position == 10 && current_page == 4)
      {
        open_weather_app();
      }
      else if (current_page == 5)
      {
        open_weather_app_2();
      }
      else if (rectangle_y_position == 30 && current_page == 4)
      {
        open_clock_app();
      }
      else if (rectangle_y_position == 50 && current_page == 4)
      {
        open_news_app();
      }
      else if (rectangle_y_position == 10 && current_page == 7)
      {
        open_general_news(rectangle_y_position);
      }
      else if (rectangle_y_position == 30 && current_page == 7)
      {
        open_general_news(rectangle_y_position);
      }
      else if (rectangle_y_position == 50 && current_page == 7)
      {
        open_general_news(rectangle_y_position);
      }
      else if (rectangle_y_position == 70 && current_page == 7)
      {
        open_general_news(rectangle_y_position);
      }
      else if (rectangle_y_position == 90 && current_page == 7)
      {
        open_general_news(rectangle_y_position);
      }
      else if (rectangle_y_position == 110 && current_page == 7)
      {
        open_general_news(rectangle_y_position);
      } else if (rectangle_y_position == 70 && current_page == 4)
      {
        open_gemeni();
      } else if (current_page == 8) // keyboard click
      {
        int c = calculate_letter_position();
        Serial.println(letters[c]);

        if (keyboard_x_position == 117 && keyboard_y_position == 117) { // check if the user pressed the space button
          tft.setCursor(letter_pos += 10, 82);
          tft.print(letters[c]);
          return;
        } else {
          tft.setCursor(letter_pos += 5, 82);
          tft.print(letters[c]);
        }
      }
    }

    // The things above this let us navigate between main pages

    delay(200);
  }
}

void initialize_buttons()
{
  pinMode(up_button, INPUT);
  pinMode(down_button, INPUT);
  pinMode(left_button, INPUT);
  pinMode(right_button, INPUT);
  pinMode(select_button, INPUT);
}

void move_up_rectangle()
{
  tft.drawRect(10, rectangle_y_position, 70, 17, ST7735_BLACK);
  rectangle_y_position -= 20;
  tft.drawRect(10, rectangle_y_position, 70, 17, ST7735_CYAN);
}
// The operators have to be reversed because the more down you go the more pixels you have so the top is 0,0 and bottom is 0,50 or sum
void move_down_rectangle()
{
  tft.drawRect(10, rectangle_y_position, 70, 17, ST7735_BLACK);
  rectangle_y_position += 20;
  tft.drawRect(10, rectangle_y_position, 70, 17, ST7735_CYAN);
}

void initialize_screen()
{
  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST7735_BLACK);
  tft.setRotation(1);
  open_main_page();
}

void initialize_loading() {
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(50, 50);
  tft.print("LOADING");
}

void initialize_keyboard() {

  int spacing = 16;
  int y_position = 98;

  for (int i = 0; i <= 25; i++) {
    if (i <= 9) {
      tft.setCursor(5 + i * spacing, y_position);
      tft.print(letters[i]);
    } else if (i <= 18) {
      tft.setCursor(5 + (i - 10) * spacing, y_position + 10);
      tft.print(letters[i]);
    } else {
      tft.setCursor(5 + (i - 19) * spacing, y_position + 20);
      tft.print(letters[i]);
      
      // Print the space button
      tft.setCursor(117,117);
      tft.print("s");
      
      //Print the enter button
      tft.setCursor(127, 117);
      tft.print("e");
    }
  }
  tft.drawRect(keyboard_x_position, keyboard_y_position, 12, 12, ST7735_CYAN);
  tft.drawLine(0, 90, 160, 90, ST7735_CYAN);
}

void move_keyboard_right() {
  if (keyboard_x_position >= 144) return;
  if (keyboard_x_position == 130 && keyboard_y_position == 106) return; // L letter block
  if (keyboard_y_position == 117 && keyboard_x_position == 114) return; // Enter letter block
  tft.drawRect(keyboard_x_position, keyboard_y_position, 12, 12, ST7735_BLACK);
  keyboard_x_position += 16;
  tft.drawRect(keyboard_x_position, keyboard_y_position, 12, 12, ST7735_CYAN);
}

void move_keyboard_left() {
  if (keyboard_x_position <= 2) return;
  tft.drawRect(keyboard_x_position, keyboard_y_position, 12, 12, ST7735_BLACK);
  keyboard_x_position -= 16;
  tft.drawRect(keyboard_x_position, keyboard_y_position, 12, 12, ST7735_CYAN);
}

void move_keyboard_up() {
  if (keyboard_y_position <= 95) return;
  tft.drawRect(keyboard_x_position, keyboard_y_position, 12, 12, ST7735_BLACK);
  keyboard_y_position -= 11;
  keyboard_row -= 1;
  tft.drawRect(keyboard_x_position, keyboard_y_position, 12, 12, ST7735_CYAN);
  delay(200);
}

void move_keyboard_down() {
  if (keyboard_y_position >= 115 || keyboard_x_position == 146) return;
  if (keyboard_y_position == 106 && keyboard_x_position == 130) return; // k and l letter block down
  tft.drawRect(keyboard_x_position, keyboard_y_position, 12, 12, ST7735_BLACK);
  keyboard_y_position += 11;
  keyboard_row += 1;
  tft.drawRect(keyboard_x_position, keyboard_y_position, 12, 12, ST7735_CYAN);
}

int calculate_letter_position() {
  int col = (int)keyboard_x_position / 16;

  if (keyboard_row == 2) {
    col += 10;
  } else if (keyboard_row == 3)
  {
    col += 19;
  }
  Serial.print(letters[col]);
  return col;
}