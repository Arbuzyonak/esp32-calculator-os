# esp32-calculator-os
An operating system for the esp32 microcontroller with Internet functionality and video games.


# Equipment needed:
- 1.8 inch tft screen
- breadboard
- jumper wires
- esp32
- 6 buttons
- antena (optional)
- usb cable to upload the code

# How to setup software
- Install the platformio extention
- import a project to platformio
- create a secrets.h file will all of your secrets
- upload the code to the esp32

# How to setup hardware
- Connect the 6 buttons to the breadboard and the esp32 (choose any pins you want. you can change them in main.cpp later)
- Conenct the screen to the esp32 (this is the best tutorial I could find, sadly it's in german so just translate the page. https://www.az-delivery.de/en/blogs/azdelivery-blog-fur-arduino-und-raspberry-pi/1-8-toll-tft-am-esp-32-dev-kit-c-betreiben)

# Showcase
- AI page
<img width="4000" height="3000" alt="20260705_190851" src="https://github.com/user-attachments/assets/09a5fb01-93b6-4267-9cd3-0b7dfb244005" />

- Main menu
<img width="4000" height="3000" alt="20260705_190950" src="https://github.com/user-attachments/assets/59b0bc6c-cb2d-477a-adfd-039a64061a77" />

- News app
<img width="4000" height="3000" alt="20260705_190939" src="https://github.com/user-attachments/assets/5158a029-dadd-414c-8900-e155ceb3066d" />

- Weather app
<img width="4000" height="3000" alt="20260705_190907" src="https://github.com/user-attachments/assets/72c90e6c-9edd-490e-8a88-50a0ed0f2f78" />

- Clock and date app
<img width="4000" height="3000" alt="20260705_190907" src="https://github.com/user-attachments/assets/7456bba8-2f4b-4972-8b45-c55e4b2a1502" />

##

**For better understanding of the code:**
- current_page = 1 -→ Main page with the Calculator, Games and Internet buttons
- current_page = 2 -→ Calculator page
- current_page = 3 -→ games page
- current_page = 4 -→ Internet page
- current_page = 5 -→ Weather app
- current_page = 6 -→ Clock app
- current_page = 7 -→ News app
- current_page = 8 -→ Groq
- current_page = 9 -→ Basic calculator

##
**Thanks for looking at my project :P**
