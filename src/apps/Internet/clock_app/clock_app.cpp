#include "apps/globals.h"


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