#include "apps/globals.h"
extern int headline;

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