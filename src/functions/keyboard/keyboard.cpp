#include "apps/globals.h"
#include "secrets.h"
extern int keyboard_x_position;
extern int keyboard_y_position;
extern int keyboard_row;
extern int letter_pos;

void get_human_message();
void open_groq();

String letters[] = {
    "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P",
    "A", "S", "D", "F", "G", "H", "J", "K", "L",
    "Z", "X", "C", "V", "B", "N", "M"};

String human_message; 

void initialize_keyboard()
{

  int spacing = 16;
  int y_position = 98;

  for (int i = 0; i <= 25; i++)
  {
    if (i <= 9)
    {
      tft.setCursor(5 + i * spacing, y_position);
      tft.print(letters[i]);
    }
    else if (i <= 18)
    {
      tft.setCursor(5 + (i - 10) * spacing, y_position + 10);
      tft.print(letters[i]);
    }
    else
    {
      tft.setCursor(5 + (i - 19) * spacing, y_position + 20);
      tft.print(letters[i]);

      // Print the space button
      tft.setCursor(117, 117);
      tft.print("s");

      // Print the delete button
      tft.setCursor(133, 117);
      tft.print("d");

      // Print the enter button
      tft.setCursor(149, 117);
      tft.print("e");
    }
  }
  tft.drawRect(keyboard_x_position, keyboard_y_position, 12, 12, ST7735_CYAN);
  tft.drawLine(0, 90, 160, 90, ST7735_CYAN); // bottom line
  tft.drawLine(0, 80, 160, 80, ST7735_CYAN); // upper line
}

void move_keyboard_right()
{
  if (keyboard_x_position >= 144)
    return;
  if (keyboard_x_position == 130 && keyboard_y_position == 106)
    return; // L letter block
  tft.drawRect(keyboard_x_position, keyboard_y_position, 12, 12, ST7735_BLACK);
  keyboard_x_position += 16;
  tft.drawRect(keyboard_x_position, keyboard_y_position, 12, 12, ST7735_CYAN);
}

void move_keyboard_left()
{
  if (keyboard_x_position <= 2)
    return;
  tft.drawRect(keyboard_x_position, keyboard_y_position, 12, 12, ST7735_BLACK);
  keyboard_x_position -= 16;
  tft.drawRect(keyboard_x_position, keyboard_y_position, 12, 12, ST7735_CYAN);
}

void move_keyboard_up()
{
  if (keyboard_y_position <= 95)
    return;
  if (keyboard_x_position == 146 && keyboard_y_position == 117) return; // Enter letter block

  tft.drawRect(keyboard_x_position, keyboard_y_position, 12, 12, ST7735_BLACK);
  keyboard_y_position -= 11;
  keyboard_row -= 1;
  tft.drawRect(keyboard_x_position, keyboard_y_position, 12, 12, ST7735_CYAN);
  delay(200);
}

void move_keyboard_down()
{
  if (keyboard_y_position >= 115 || keyboard_x_position == 146)
    return;
  //if (keyboard_y_position == 106 && keyboard_x_position == 130)
    //return; // k and l letter block down
  tft.drawRect(keyboard_x_position, keyboard_y_position, 12, 12, ST7735_BLACK);
  keyboard_y_position += 11;
  keyboard_row += 1;
  tft.drawRect(keyboard_x_position, keyboard_y_position, 12, 12, ST7735_CYAN);
}

int calculate_letter_position()
{
  int col = (int)keyboard_x_position / 16;

  if (keyboard_row == 2)
  {
    col += 10;
  }
  else if (keyboard_row == 3)
  {
    col += 19;
  }
  return col;
}

void print_keyboard_letters() {
  if (letter_pos >= 150) return; // max word limit

  if (keyboard_x_position == 114 && keyboard_y_position == 117) 
  { // Space button
    letter_pos += 5;
    get_human_message();
    return;
  }

  if (keyboard_x_position == 130 && keyboard_y_position == 117) // delete text button
  {
    tft.fillRect(0, 81, 160, 9, ST7735_BLACK);
    human_message = "";
  }

  if (keyboard_x_position == 146 && keyboard_y_position == 117)
  { // Send a request to groq
    tft.fillRect(0, 0, 160, 79, ST7735_BLACK);
    open_groq();
    human_message = "";
    return;
  }

  int c = calculate_letter_position();
  tft.setCursor(letter_pos += 5, 82);
  tft.print(letters[c]);
  get_human_message();
}

void get_human_message()
{
  int c = calculate_letter_position();
  
  if (keyboard_x_position == 114 && keyboard_y_position == 117)
  {
    human_message += " ";
    Serial.println(human_message);
    Serial.println(keyboard_x_position);
    return;
  }
  else
  {
    human_message += String(letters[c]);
    Serial.println(human_message);
    Serial.println(keyboard_x_position);
  }
}

void open_groq()
{
  WiFiClientSecure client;
  client.setInsecure(); 

  HTTPClient http;
  http.begin(client, "https://api.groq.com/openai/v1/chat/completions");
  http.addHeader("Content-Type", "application/json");
  http.addHeader("Authorization", "Bearer " + GROQ_API_KEY);

  JsonDocument reqDoc;
  reqDoc["model"] = "openai/gpt-oss-20b";
  JsonArray messages = reqDoc["messages"].to<JsonArray>();
  JsonObject msg = messages.add<JsonObject>();
  msg["role"] = "user";
  msg["content"] = human_message;

  String requestBody;
  serializeJson(reqDoc, requestBody);

  tft.setCursor(0, 5);
  tft.print("Loading..."); // loading message

  int responseCode = http.POST(requestBody);
  String response = http.getString();

  JsonDocument respDoc;
  deserializeJson(respDoc, response);
  String reply = respDoc["choices"][0]["message"]["content"];

  tft.fillRect(0,0,160,79, ST7735_BLACK); // fill in the loading message

  tft.setCursor(2,5);
  tft.print(reply);

  http.end();
}