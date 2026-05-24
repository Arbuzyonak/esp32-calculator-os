#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// Notes: use canvaces instead of directly printing // Instead of buttons use http and a browser for now //

// News api key = 01c6dc4af25e478cad5ba179626dfe3e

const char *ssid = "Arbuzik";
const char *password = "Nassif2026";

// tft object variables
const int TFT_CS = 5;
const int TFT_DC = 4;
const int TFT_RST = 2;

// button variables
const int up_button = 34;
const int down_button = 17;
const int select_button = 19;

const int CLK = 35;
const int DT = 32;
const int SW = 33; // Change all of these numbers cuz they aint workin

int counter = 0;
int currentStateCLK;
int lastStateCLK;

int rectangle_y_position = 10;

int current_page = 1;

int headline = 0;

bool scroll = true;

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void initialize_screen();  // Start up screen
void initialize_buttons(); // pinMode setup
void initialize_loading();

void move_up_rectangle();   // Move the select rectangle 20 pixels up
void move_down_rectangle(); // Move the select rectangle 20 pixels down

void open_main_page();       // Draw the main screen the Calculator, Games and Internet buttons
void open_calculator_page(); // Open the page with all the functions for math
void open_games_page();      // Open the page with all the games
void open_internet_page();   // Open the page with all the internet apps

void open_weather_app();   // Get weather data for  Montreal
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
  WiFi.begin(ssid, password);

  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
  pinMode(SW, PULLUP);
  lastStateCLK = digitalRead(CLK);
  // tft.drawRect(10, 10, 75, 20, ST77XX_BLACK);
}

void loop()
{

  {
    currentStateCLK = digitalRead(CLK);
    if (currentStateCLK != lastStateCLK && currentStateCLK == 1)
    {
      if (digitalRead(DT) != currentStateCLK)
      {
        counter++; // Clockwise
      }
      else
      {
        counter--; // Counter-clockwise
      }
      Serial.println(counter);
    }
    lastStateCLK = currentStateCLK;

    if (digitalRead(up_button) == HIGH && digitalRead(down_button) == HIGH)
    { // Go to the main page from the calcualtor page
      if (current_page == 1)
        return;

      open_main_page();
      tft.setTextSize(1);
      current_page = 1;
      headline = 0;
      scroll = true;
    }

    if (digitalRead(up_button) == HIGH)
    { // go up
      if (scroll == false)
        return;

      if (rectangle_y_position == 10)
        return;
      move_up_rectangle();
    }

    if (digitalRead(down_button) == HIGH)
    { // go down
      if (scroll == false)
        return;

      Serial.println(rectangle_y_position);
      if (rectangle_y_position >= 50 && !(current_page == 3 || current_page == 4 || current_page == 7))
        return;
      if (rectangle_y_position >= 90 && (current_page == 3 || current_page == 4))
        return;
      if (rectangle_y_position >= 110 && (current_page == (7)))
        return;
      move_down_rectangle();
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

void open_main_page()
{
  rectangle_y_position = 10;
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(15, 15);
  tft.setTextColor(ST7735_CYAN);
  tft.print("Calculator");

  tft.setCursor(15, 35);
  tft.setTextColor(ST7735_CYAN);
  tft.print("Games");

  tft.setCursor(15, 55);
  tft.setTextColor(ST7735_CYAN);
  tft.print("Internet");

  tft.drawRect(10, rectangle_y_position, 70, 17, ST7735_CYAN);
}

void open_calculator_page()
{
  current_page = 2; // !!! Page 1 = Main page; Page 2 = Calculator; Page 3 = Games; Page 4 = Internet;
  rectangle_y_position = 10;
  tft.fillScreen(ST7735_BLACK);

  tft.setCursor(15, 15);
  tft.setTextColor(ST7735_CYAN);
  tft.print("Basic");

  tft.setCursor(15, 35);
  tft.setTextColor(ST7735_CYAN);
  tft.print("Converter");

  tft.setCursor(15, 55);
  tft.setTextColor(ST7735_CYAN);
  tft.print("Functions");

  tft.drawRect(10, rectangle_y_position, 70, 17, ST7735_CYAN);
}

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

void open_internet_page()
{
  current_page = 4;
  rectangle_y_position = 10;
  tft.fillScreen(ST7735_BLACK);

  tft.setCursor(15, 15);
  tft.setTextColor(ST7735_CYAN);
  tft.print("Weather");

  tft.setCursor(15, 35);
  tft.setTextColor(ST7735_CYAN);
  tft.print("Clock ");

  tft.setCursor(15, 55);
  tft.setTextColor(ST7735_CYAN);
  tft.print("News");

  tft.setCursor(15, 75);
  tft.setTextColor(ST7735_CYAN);
  tft.print("Gemeni");

  tft.setCursor(15, 95);
  tft.setTextColor(ST7735_CYAN);
  tft.print("Home Server");

  tft.drawRect(10, rectangle_y_position, 70, 17, ST7735_CYAN);
}

void open_weather_app()
{
  current_page = 5;
  scroll = false;

  HTTPClient http;
  http.begin("https://api.open-meteo.com/v1/gem/?latitude=45.5&longitude=-73.57&current=temperature_2m,rain,snowfall,precipitation,cloud_cover,wind_speed_10m");

  initialize_loading();

  int responseCode = http.GET();
  String response = http.getString();

  JsonDocument doc;
  deserializeJson(doc, response);

  float temperature = doc["current"]["temperature_2m"];
  float rain = doc["current"]["rain"];
  float snowfall = doc["current"]["snowfall"];
  float precipitation = doc["current"]["precipitation"];
  float cloud_cover = doc["current"]["cloud_cover"];
  float wind_speed_10m = doc["current"]["wind_speed_10m"];

  tft.fillScreen(ST7735_BLACK);

  tft.setCursor(10, 10);
  tft.print("Temperature:" + String(temperature) + "C");

  tft.setCursor(10, 30);
  tft.print("Rain:" + String(rain) + "mm");

  tft.setCursor(10, 50);
  tft.print("Snowfall:" + String(snowfall) + "cm");

  tft.setCursor(10, 70);
  tft.print("Precipitation:" + String(precipitation) + "mm");

  tft.setCursor(10, 90);
  tft.print("Cloud cover:" + String(cloud_cover) + "%");

  tft.setCursor(10, 110);
  tft.print("Wind speed:" + String(wind_speed_10m) + "km/h");

  http.end();
}

void open_weather_app_2()
{
  current_page = 5;
  scroll = false;

  HTTPClient http;
  http.begin("https://api.open-meteo.com/v1/gem/?latitude=45.5&longitude=-73.57&timezone=America%2FToronto&daily=sunrise,sunset&current=relative_humidity_2m");

  initialize_loading();

  int responseCode = http.GET();
  String response = http.getString();

  JsonDocument doc;
  deserializeJson(doc, response);

  String sunrise = doc["daily"]["sunrise"];
  String sunset = doc["daily"]["sunset"];
  String relative_humidity_2m = doc["current"]["relative_humidity_2m"];

  int sunrise_index_pos = sunrise.indexOf("T");
  String sunrise_time = sunrise.substring(sunrise_index_pos + 1, sunrise_index_pos + 6);

  int sunset_index_pos = sunrise.indexOf("T");
  String sunset_time = sunset.substring(sunset_index_pos + 1, sunset_index_pos + 6);

  tft.fillScreen(ST7735_BLACK);

  tft.setCursor(10, 10);
  tft.print("Sunrise:" + sunrise_time + " AM");

  tft.setCursor(10, 30);
  tft.print("Sunset:" + sunset_time + " PM");

  tft.setCursor(10, 50);
  tft.print("Humidity:" + relative_humidity_2m + "%");

  http.end();
}

void open_clock_app()
{
  current_page = 6;
  scroll = false;

  HTTPClient http;
  http.begin("https://timeapi.io/api/v1/timezone/zone?timeZone=America%2FToronto");

  initialize_loading();

  int responseCode = http.GET();
  String response = http.getString();

  JsonDocument doc;
  deserializeJson(doc, response);

  String day_of_week = doc["day_of_week"];
  String date = doc["local_time"];

  int date_index_pos = date.indexOf("T");
  String date_string = date.substring(0, date_index_pos);
  String time_string = date.substring(date_index_pos + 1, date_index_pos + 8);

  tft.fillScreen(ST7735_BLACK);

  tft.setCursor(10, 10);
  tft.print("Today Is " + day_of_week);

  tft.setCursor(10, 30);
  tft.print("Date:" + date_string);

  tft.setCursor(10, 50);
  tft.print("Time:" + time_string);

  http.end();
}

void open_news_app()
{
  current_page = 7;

  tft.fillScreen(ST7735_BLACK);

  rectangle_y_position = 10;
  tft.drawRect(10, rectangle_y_position, 70, 17, ST7735_CYAN);

  tft.setCursor(15, 15);
  tft.print("General");

  tft.setCursor(15, 35);
  tft.print("Technology");

  tft.setCursor(15, 55);
  tft.print("Science");

  tft.setCursor(15, 75);
  tft.print("Health");

  tft.setCursor(15, 95);
  tft.print("Entertainment");

  tft.setCursor(15, 115);
  tft.print("Business");
}

void open_general_news(int position)
{
  scroll = false;
  headline = headline + 1;

  HTTPClient http;

  if (position == 10)
  {
    http.begin("https://newsapi.org/v2/top-headlines?category=general&apiKey=01c6dc4af25e478cad5ba179626dfe3e");
  }
  else if (position == 30)
  {
    http.begin("https://newsapi.org/v2/top-headlines?category=technology&apiKey=01c6dc4af25e478cad5ba179626dfe3e");
  }
  else if (position == 50)
  {
    http.begin("https://newsapi.org/v2/top-headlines?category=science&apiKey=01c6dc4af25e478cad5ba179626dfe3e");
  }
  else if (position == 70)
  {
    http.begin("https://newsapi.org/v2/top-headlines?category=health&apiKey=01c6dc4af25e478cad5ba179626dfe3e");
  }
  else if (position == 90)
  {
    http.begin("https://newsapi.org/v2/top-headlines?category=entertainment&apiKey=01c6dc4af25e478cad5ba179626dfe3e");
  }
  else if (position == 110)
  {
    http.begin("https://newsapi.org/v2/top-headlines?category=business&apiKey=01c6dc4af25e478cad5ba179626dfe3e");
  }

  initialize_loading();

  int responseCode = http.GET();
  String response = http.getString();

  JsonDocument doc;
  deserializeJson(doc, response);

  String headline_source = doc["articles"][headline]["source"]["name"];
  String headline_title = doc["articles"][headline]["title"];
  String headline_description = doc["articles"][headline]["description"];

  Serial.print(headline);

  tft.fillScreen(ST7735_BLACK);

  tft.setCursor(5, 5);
  tft.print(headline_source);

  tft.setTextSize(0.5);

  tft.setCursor(0, 20);
  tft.print(headline_title + ":" + "\n" + headline_description);

  http.end();
}

void open_gemeni() {
  current_page = 8;
  scroll = false;

  tft.fillScreen(ST7735_BLACK);
}