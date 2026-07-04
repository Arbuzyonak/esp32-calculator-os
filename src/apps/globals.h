#ifndef GLOBALS_H
#define GLOBALS_H


#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

extern Adafruit_ST7735 tft;
extern int current_page;
extern bool scroll;
extern int rectangle_y_position;
extern int initialize_loading();

#endif