#include "apps/globals.h"

void open_weather_app()
{
  current_page = 5;
  scroll = false;


  WiFiClientSecure client;
  client.setInsecure();
  
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