# The-Wizard-of-Eldoria
This is my project for a handheld text based game called "The Wizard of Eldoria".
(links posted to this readme on 12/27/2023)

The inspiration for this project came from user Warmcats at instructables.com
https://www.instructables.com/Text-Based-Multi-Choice-Adventure-Game/

The story is my own creation. It was written out of my general love for the
Fantasy genre.

My project uses different hardware. The primary reason is that my story requires more memory.
The Arduino used in Warmcat's project uses an ATmega328P microcontroller which has 32KB flash memory and 2KB SRAM.
I defaulted to an Arduino Mega which uses the ATmega2560 microcontroller which has 256K flash memory and 8KB SRAM.

The hardware required for this project includes:
- Arduino Mega (https://www.amazon.com/gp/product/B01H4ZDYCE/ref=ppx_yo_dt_b_asin_title_o01_s00?ie=UTF8&th=1)
- 3.5" TFT LCD display (https://www.amazon.com/gp/product/B073R7Q8FF/ref=ppx_yo_dt_b_asin_title_o01_s00?ie=UTF8&psc=1)
- PCB board
- 4x momentary SPST push button switches

The case for the handheld was designed by me in Tinkercad:
https://www.tinkercad.com/things/iZI8byJxRm4-35-tft-screen-arduino-mega-game-case

The required files to flash to the arduino Mega include:
WizardGame.ino
strings.h

Include the follwoing library:
TFT_HX8357.h (https://github.com/Bodmer/TFT_HX8357)
