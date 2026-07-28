# esp32-calculator-os

A handheld calculator OS I built from scratch on an ESP32. With an AI assistant, weather, news, a clock, and games, all on a 1.8" screen and six buttons.

I made it because I wanted something on my desk at school that could do more than arithmetics. So it runs a little OS: a main menu, apps you can navigate to with the buttons, and an AI page I can actually ask questions.

**Demo video:** https://www.youtube.com/watch?v=k9yE6ENTkz4

---

## What it does

- **Calculator**
- **AI page** type a question on the on-screen keyboard
- **Weather app** current weather conditions
- **News app** headlines pulled from an api
- **Clock** self explanatory
- **Games** none yet
- **Color themes**  cyan, green, red, white

## Showcase
 
| Main menu | Settings |
|---|---|
| <img width="400" alt="Main menu with Calculator, Games, Internet and Settings" src="https://github.com/user-attachments/assets/fb372ba4-4c8d-4c4f-9246-cd5a9df61c68" /> | <img width="400" alt="Settings page" src="https://github.com/user-attachments/assets/b859296f-8a4e-4120-b5dc-e30d4e859f69" /> |
 
| Calculator | Calculator result |
|---|---|
| <img width="400" alt="Calculator with 66+67 entered" src="https://github.com/user-attachments/assets/17944d9f-cc64-45ad-a1e4-cfcbb5ef89a8" /> | <img width="400" alt="Calculator showing the result 133" src="https://github.com/user-attachments/assets/f061e6df-643a-497d-bfc6-a318da526954" /> |
 
| AI page | News app |
|---|---|
| <img width="400" alt="AI page answering a question over WiFi" src="https://github.com/user-attachments/assets/fdcb7176-ef0f-45a8-97dd-41369b8e3a94" /> | <img width="400" alt="News app showing headlines" src="https://github.com/user-attachments/assets/903e84fe-826d-44be-856f-60d054d43bb2" /> |
 
| Weather app | Weather |
|---|---|
| <img width="400" alt="Weather app" src="https://github.com/user-attachments/assets/d8558359-03ed-4203-aa87-17957b1cc312" /> | <img width="400" alt="Weather forecast view" src="https://github.com/user-attachments/assets/bb9ea939-75ae-4a52-8f58-762eea11c7f3" /> |

## Equipment needed

| Part | Notes |
|---|---|
| ESP32 dev board | Any WROOM-32 board works |
| 1.8" TFT screen | ST7735 driver, SPI |
| 6 × push buttons | Navigation + select |
| Breadboard | |
| Jumper wires | |
| USB cable | For flashing |
| Antenna | Optional |

## Wiring

| Signal | ESP32 pin |
|---|---|
| TFT CS | 5 |
| TFT DC / A0 | 4 |
| TFT RST | 2 |
| TFT SDA / MOSI | 23 |
| TFT SCK | 18 |
| TFT LED / BL | 3V3 |
| TFT VCC | 3V3 |
| TFT GND | GND |
| Button - up | 34 |
| Button - down | 17 |
| Button - left | 13 |
| Button - right | 12 |
| Button - select | 19 |
 
All pins are defined at the top of `main.cpp`, so you can change them to whatever's free on your board.

Screen wiring reference (in German — translate the page, it's the clearest one I found):
https://www.az-delivery.de/en/blogs/azdelivery-blog-fur-arduino-und-raspberry-pi/1-8-toll-tft-am-esp-32-dev-kit-c-betreiben

## Setup

**1. Install PlatformIO** (VS Code extension), then open this repo as a PlatformIO project.

**2. Create `src/secrets.h`** with your own credentials:

```cpp
#define WIFI_SSID     "your-network-name"
#define WIFI_PASSWORD "your-wifi-password"
#define GROQ_API_KEY  "gsk_your_key_here"
```

Get a free Groq API key at https://console.groq.com.

**3. Wire it up** per the table above.

**4. Upload** with PlatformIO's upload button, or `pio run -t upload`.

## How the code is laid out

Navigation is driven by the `current_page` variable.

| `current_page` | Screen |
|---|---|
| 1 | Main menu (Calculator / Games / Internet) |
| 2 | Calculator menu |
| 3 | Games |
| 4 | Internet |
| 5 | Weather app |
| 6 | Clock |
| 7 | News |
| 8 | Groq |
| 9 | Basic calculator |

## limitations

- Needs WiFi for the AI, weather, and news pages

## Roadmap

- games

---

**Thanks for looking at my project :P**
