/*
Revision History

V0.1
Player can travel to all major locations (N, S, E ,W)
Player can collect the 3 major items (Cloak, Orb, Sword)
Player cannot return to major area if item was collected
A basic Inventory shows if items have been collected.
Dying or Winning the game clears inventory
Prompt text needs work

V0.2
Beginning of story is in place from computer to wizard letter
Ran into issue with memory storage 

V0.3
Transitioning strings to flash memory which uses strings.h
Made minor updates to text fields and spacing

V0.4
Organized all scenes alphabetically for easier finding
completed the ghostship storyline.
hardware changing button pins from 4,5,6,7 to 10,11,12,13

v0.5
Rewrote "Start" text
made uniform the phrase press any key (got rid of press any button)
added water as an inventory item
West storylines complete

v0.6
included the chloe story.
more work on desert area.
tandirith story line started.
ending added.

v0.7
standardized spacing for choice box
added line for choice box
*/

#include <TFT_HX8357.h>
#include <User_Setup.h>
#include "Strings.h"

TFT_HX8357 tft = TFT_HX8357();

//Global variables
void (*state)() = NULL;
boolean haveOrb = 0;     //uncomment for gameplay
boolean haveCloak = 0;   //uncomment for gameplay
boolean haveSword = 0;   //uncomment for gameplay
boolean haveCosmos = 0;  //uncomment for gameplay
//boolean haveOrb = 1;     //used for development comment out for gameplay
//boolean haveCloak = 1;   //used for development comment out for gameplay
//boolean haveSword = 1;   //used for development comment out for gameplay
//boolean haveCosmos = 1;  //used for development comment out for gameplay
int water = 0;
int previousWater = 0;
char buffer[40];

const int buttonPin1 = 10;
const int buttonPin2 = 11;
const int buttonPin3 = 12;
const int buttonPin4 = 13;
boolean buttonState1 = 1;
boolean buttonState2 = 1;
boolean buttonState3 = 1;
boolean buttonState4 = 1;
boolean lastButtonState1 = 1;
boolean lastButtonState2 = 1;
boolean lastButtonState3 = 1;
boolean lastButtonState4 = 1;
long lastDebounce1 = 0;
long lastDebounce2 = 0;
long lastDebounce3 = 0;
long lastDebounce4 = 0;

void setup() {
  tft.begin();                  //Initiates screen
  tft.setRotation(1);           //rotates the screen from portrait to landscape
  tft.fillScreen(TFT_BLACK);    //clears the screen to black color
  tft.setTextFont(1);           //sets font to default font
  tft.setTextSize(3);           //sets font size to 3
  tft.setTextColor(TFT_WHITE);  //sets font color to white
  tft.setCursor(0, 40);         //Sets cursor to position x,y
  tft.println("   The Wizard of Eldoria");
  tft.setTextSize(2);  //sets font size to 2
  tft.println("        A Text Based Adventure");
  tft.setCursor(0, 110);
  tft.println();
  tft.println("        To Matthew From Daniel");
  tft.println("            Christmas 2023");
  tft.setCursor(0, 230);
  tft.println("         Press any key to start");
  tft.setCursor(0, 300);
  tft.setTextSize(1);
  tft.println("v0.7");
  tft.setTextSize(2);

  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buttonPin4, INPUT_PULLUP);

  int buttonPressed = ButtonChoice();
  state = start_1;  //Set starting area
}

void loop() {
  state();  //fetch current area
  delay(10);
}

//*********************************************************************************************************
//BUTTON CODE *********************************************************************************************
//*********************************************************************************************************
int ButtonChoice() {
  int buttonChosen = 0;
  while (buttonChosen == 0) {
    int buttonReading1 = digitalRead(buttonPin1);
    int buttonReading2 = digitalRead(buttonPin2);
    int buttonReading3 = digitalRead(buttonPin3);
    int buttonReading4 = digitalRead(buttonPin4);
    if (buttonReading1 != lastButtonState1) { lastDebounce1 = millis(); }
    if (buttonReading2 != lastButtonState2) { lastDebounce2 = millis(); }
    if (buttonReading3 != lastButtonState3) { lastDebounce3 = millis(); }
    if (buttonReading4 != lastButtonState4) { lastDebounce4 = millis(); }
    //  BUTTON 1
    if ((millis() - lastDebounce1) > 50) {
      if (buttonReading1 != buttonState1) {  //button really has changed state
        buttonState1 = buttonReading1;
        if (buttonState1 == LOW) {  //only if button pressed
          buttonChosen = 1;
        }
      }
    }
    //  BUTTON 2
    if ((millis() - lastDebounce2) > 50) {
      if (buttonReading2 != buttonState2) {  //button really has changed state
        buttonState2 = buttonReading2;
        if (buttonState2 == LOW) {  //only if button pressed
          buttonChosen = 2;
        }
      }
    }
    //  BUTTON 3
    if ((millis() - lastDebounce3) > 50) {
      if (buttonReading3 != buttonState3) {  //button really has changed state
        buttonState3 = buttonReading3;
        if (buttonState3 == LOW) {  //only if button pressed
          buttonChosen = 3;
        }
      }
    }
    //  BUTTON 4
    if ((millis() - lastDebounce4) > 50) {
      if (buttonReading4 != buttonState4) {  //button really has changed state
        buttonState4 = buttonReading4;
        if (buttonState4 == LOW) {  //only if button pressed
          buttonChosen = 4;
        }
      }
    }
    // Save readings for next loop
    lastButtonState1 = buttonReading1;
    lastButtonState2 = buttonReading2;
    lastButtonState3 = buttonReading3;
    lastButtonState4 = buttonReading4;
  }
  return buttonChosen;
}

void (*resetFunc)(void) = 0;

//******************************************************************************************************
// ALL SCENES ordered alphabetically********************************************************************
//******************************************************************************************************

//Alton 1 *********************************************************************************************
void alton_1() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 12; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(alton1[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = alton_2;
}

//Alton 2 *********************************************************************************************
void alton_2() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 13; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(alton2[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = alton_3;
}

//Alton 3 *********************************************************************************************
void alton_3() {

  //Recall Text from Flash
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 12; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(alton3[i])));
    tft.println(buffer);
  }

  tft.drawLine(0, 245, 480, 245, TFT_WHITE);
  tft.setCursor(0, 250);
  tft.println("1.\"I see a pale green light to port.\"");
  tft.println("2.\"I see a yellow light to starboard.\"");

  int buttonPressed = ButtonChoice();
  boolean buttonPressReq = 0;
  switch (buttonPressed) {
    case 1:
      buttonPressReq = 1;
      state = seamonster_1;
      break;
    case 2:
      buttonPressReq = 1;
      state = lighthouse_1;
      break;
  }
}

//Chloe 1 *********************************************************************************************
void chloe_1() {

  //Recall Text from Flash
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 6; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(chloe1[i])));
    tft.println(buffer);
  }

  if ((haveCloak == 1) && (haveOrb == 1) && (haveSword == 1)) {
    tft.setCursor(0, 130);
    tft.println("  \"Yes, I have them all!\" you say");
    tft.println("proudly.");
    tft.setCursor(160, 270);
    tft.println("press any key");
    int buttonPressed = ButtonChoice();
    state = chloe_3;
  } else {
    tft.drawLine(0, 245, 480, 245, TFT_WHITE);
    tft.setCursor(0, 250);
    tft.println("1. \"No, I am still looking.\"");
    tft.println("2. \"Can you give me any hints?\"");
    tft.println("3. Go back to the town squre.");
    int buttonPressed = ButtonChoice();
    boolean buttonPressReq = 0;
    switch (buttonPressed) {
      case 1:
        buttonPressReq = 1;
        state = chloe_2;
        break;
      case 2:
        buttonPressReq = 1;
        state = hint;
        break;
      case 3:
        buttonPressReq = 1;
        state = townSquare_1;
        break;
    }
  }
}

//Chloe 2 *********************************************************************************************
void chloe_2() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 4; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(chloe2[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = chloe_1;
}

//Chloe 3 *********************************************************************************************
void chloe_3() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 6; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(chloe3[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = chloe_4;
}

//Chloe 4 *********************************************************************************************
void chloe_4() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 11; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(chloe4[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = chloe_5;
}

//Chloe 5 *********************************************************************************************
void chloe_5() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 9; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(chloe5[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = chloe_6;
}

//Chloe 6 *********************************************************************************************
void chloe_6() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 10; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(chloe6[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = chloe_7;
}

//Chloe 7 *********************************************************************************************
void chloe_7() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 9; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(chloe7[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = chloe_8;
}

//Chloe 8 *********************************************************************************************
void chloe_8() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 8; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(chloe8[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = chloe_9;
}

//Chloe 9 *********************************************************************************************
void chloe_9() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 14; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(chloe9[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = chloe_10;
}

//Chloe 10 *********************************************************************************************
void chloe_10() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 12; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(chloe10[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = chloe_11;
}

//Chloe 11 *********************************************************************************************
void chloe_11() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 4; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(chloe11[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = chloe_12;
}

//Chloe 12 *********************************************************************************************
void chloe_12() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 14; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(chloe12[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = chloe_13;
}

//Chloe 13 *********************************************************************************************
void chloe_13() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 13; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(chloe13[i])));
    tft.println(buffer);
  }

  haveCosmos = 1;  //You now have the know how to enchant the sword!

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = chloe_14;
}

//Chloe 14 *********************************************************************************************
void chloe_14() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 4; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(chloe14[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = townSquare_3;
}

//Dead *********************************************************************************************
void dead() {

  // reset inventory
  haveCloak = 0;
  haveOrb = 0;
  haveSword = 0;
  water = 0;
  previousWater = 0;

  // prepare screen and print text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  tft.println("You died.");

  //prompt option and wait for button press
  tft.setCursor(0, 240);
  tft.println("Play Again?");
  tft.println(" ");
  tft.println("1. Start from Intro");
  tft.println("2. Skip Intro");
  int buttonPressed = ButtonChoice();
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  boolean buttonPressReq = 0;
  switch (buttonPressed) {
    case 1:
      buttonPressReq = 1;
      resetFunc();
      break;
    case 2:
      buttonPressReq = 1;
      state = townSquare_1;
      break;
  }
}

//Dead Thirst *********************************************************************************************
void dead_thirst() {

  // reset inventory
  haveCloak = 0;
  haveOrb = 0;
  haveSword = 0;
  water = 0;
  previousWater = 0;

  // prepare screen and print text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  tft.println("You ran out of water and died.");

  //prompt option and wait for button press
  tft.setCursor(0, 240);
  tft.println("Play Again?");
  tft.println(" ");
  tft.println("1. Start from Intro");
  tft.println("2. Skip Intro");
  int buttonPressed = ButtonChoice();
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  boolean buttonPressReq = 0;
  switch (buttonPressed) {
    case 1:
      buttonPressReq = 1;
      resetFunc();
      break;
    case 2:
      buttonPressReq = 1;
      state = townSquare_1;
      break;
  }
}

//Desert 1 *********************************************************************************************
void desert_1() {

  //Water meter
  tft.setCursor(0, 290);
  tft.print(water);
  tft.print(" liters of water");

  if (haveOrb == 1) {
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(0, 10);
    for (int i = 0; i < 7; i++) {
      strcpy_P(buffer, (char*)pgm_read_word(&(desertOrb1[i])));
      tft.println(buffer);
    }
    tft.setCursor(0, 270);
    tft.println("press any key");
    int buttonPressed = ButtonChoice();
    state = desertOrb_2;
  } else {
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(0, 10);
    for (int i = 0; i < 7; i++) {
      strcpy_P(buffer, (char*)pgm_read_word(&(desert1[i])));
      tft.println(buffer);
    }
    tft.setCursor(160, 270);
    tft.println("press any key");
  }
  int buttonPressed = ButtonChoice();
  state = desert_2;
}

//Desert 2 *********************************************************************************************
void desert_2() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 7; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(desert2[i])));
    tft.println(buffer);
  }

  //Water meter
  tft.setCursor(0, 290);
  tft.print(water);
  tft.print(" liters of water");

  //options
  tft.drawLine(0, 245, 480, 245, TFT_WHITE);
  tft.setCursor(0, 250);
  tft.println("1. To the dunes (1-day)");
  tft.println("2. To the oasis (1-day)");
  tft.println("3. Go back to town");

  int buttonPressed = ButtonChoice();
  boolean buttonPressReq = 0;
  switch (buttonPressed) {
    case 1:
      buttonPressReq = 0;
      state = dunes_1;
      break;
    case 2:
      buttonPressReq = 1;
      state = oasis_1;
      break;
    case 3:
      buttonPressReq = 1;
      state = townSquare_1;
      break;
  }
}

//Desert Orb 2 *********************************************************************************************
void desertOrb_2() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 7; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(desertOrb2[i])));
    tft.println(buffer);
  }

  //Water meter
  tft.setCursor(0, 290);
  tft.print(water);
  tft.print(" liters of water");

  //options
  tft.drawLine(0, 245, 480, 245, TFT_WHITE);
  tft.setCursor(0, 250);
  tft.println("1. To the dunes (1-day)");
  tft.println("2. To the oasis (1-day)");
  tft.println("3. Go back to town");

  int buttonPressed = ButtonChoice();
  boolean buttonPressReq = 0;
  switch (buttonPressed) {
    case 1:
      buttonPressReq = 0;
      state = dunes_1;
      break;
    case 2:
      buttonPressReq = 1;
      state = oasis_1;
      break;
    case 3:
      buttonPressReq = 1;
      state = townSquare_1;
      break;
  }
}

//Docks 1 *********************************************************************************************
void docks_1() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 14; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(docks1[i])));
    tft.println(buffer);
  }

  //Prompts
  tft.drawLine(0, 245, 480, 245, TFT_WHITE);
  tft.setCursor(0, 250);
  tft.println("1.\"Yes, I am your man. Let's go.\"");
  tft.println("2.\"I am looking for a man named\"");
  tft.println("   Malcom. Do you know him?\"");

  //Selections
  int buttonPressed = ButtonChoice();
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  boolean buttonPressReq = 0;
  switch (buttonPressed) {
    case 1:
      buttonPressReq = 1;
      state = alton_1;
      break;
    case 2:
      buttonPressReq = 1;
      state = docks_2;
      break;
  }
}

//Docks 2 *********************************************************************************************
void docks_2() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 7; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(docks2[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = malcolm_1;
}

//Dunes 1 *********************************************************************************************
void dunes_1() {

  //Calculate new water level
  if (haveOrb == 1) {
    water = water - 1;  //night water loss
  } else {
    water = water - 2;
  }

  if (water < 0) {
    state = dead_thirst;
  } else {
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(0, 10);
    for (int i = 0; i < 11; i++) {
      strcpy_P(buffer, (char*)pgm_read_word(&(dunes1[i])));
      tft.println(buffer);
    }

    //Water meter
    tft.setCursor(0, 290);
    tft.print(water);
    tft.print(" liters of water");

    tft.setCursor(160, 270);
    tft.println("press any key");
    int buttonPressed = ButtonChoice();
    state = dunes_2;
  }
}

//Dunes 2 *********************************************************************************************
void dunes_2() {

  water = water - 1;
  if (water < 0) {
    state = dead_thirst;
  } else {
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(0, 10);
    for (int i = 0; i < 12; i++) {
      strcpy_P(buffer, (char*)pgm_read_word(&(dunes2[i])));
      tft.println(buffer);
    }

    //Water meter
    tft.setCursor(0, 290);
    tft.print(water);
    tft.print(" liters of water");

    tft.setCursor(160, 270);
    tft.println("press any key");
    int buttonPressed = ButtonChoice();
    state = dunes_3;
  }
}

//Dunes 3 *********************************************************************************************
void dunes_3() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 6; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(dunes3[i])));
    tft.println(buffer);
  }

  //Prompts
  tft.drawLine(0, 245, 480, 245, TFT_WHITE);
  tft.setCursor(0, 250);
  tft.println("1. Explore giant scorpion (1-day)");
  tft.println("2. Go back to Ravenrock (1-day)");

  //Water meter
  tft.setCursor(0, 290);
  tft.print(water);
  tft.print(" liters of water");

  //Selections
  int buttonPressed = ButtonChoice();
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  boolean buttonPressReq = 0;
  switch (buttonPressed) {
    case 1:
      buttonPressReq = 1;
      state = scorpion_1;
      break;
    case 2:
      buttonPressReq = 1;
      state = dunes_4;
      break;
  }
}

//Dunes 4 *********************************************************************************************
void dunes_4() {

  water = water - 2;
  if (water < 0) {
    state = dead_thirst;
  } else {
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(0, 10);
    for (int i = 0; i < 6; i++) {
      strcpy_P(buffer, (char*)pgm_read_word(&(dunes4[i])));
      tft.println(buffer);
    }
  }
  //Water meter
  tft.setCursor(0, 290);
  tft.print(water);
  tft.print(" liters of water");

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = townSquare_1;
}

//Ending 1 *********************************************************************************************
void ending_1() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 3; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(ending1[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = ending_2;
}

//Ending 2 *********************************************************************************************
void ending_2() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 11; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(ending2[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = ending_3;
}

//Ending 3 *********************************************************************************************
void ending_3() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 9; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(ending3[i])));
    tft.println(buffer);
  }

  //Prompts
  tft.drawLine(0, 245, 480, 245, TFT_WHITE);
  tft.setCursor(0, 250);
  tft.println("1. Go back home");
  tft.println("2. Stay in Eldoria");

  //Selections
  int buttonPressed = ButtonChoice();
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  boolean buttonPressReq = 0;
  switch (buttonPressed) {
    case 1:
      buttonPressReq = 1;
      state = ending_4;
      break;
    case 2:
      buttonPressReq = 1;
      state = ending_4;
      break;
  }
}

//Ending 4 *********************************************************************************************
void ending_4() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(150, 200);
  for (int i = 0; i < 1; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(ending4[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  resetFunc();
}

//Forest 1 *********************************************************************************************
void forest_1() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 8; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(forest1[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = forest_2;
}

//Forest 2 *********************************************************************************************
void forest_2() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 9; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(forest2[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = forest_3;
}

//Forest 3 *********************************************************************************************
void forest_3() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 6; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(forest3[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = forest_4;
}

//Forest 4 *********************************************************************************************
void forest_4() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 12; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(forest4[i])));
    tft.println(buffer);
  }

  //Prompts
  tft.drawLine(0, 245, 480, 245, TFT_WHITE);
  tft.setCursor(0, 250);
  tft.println("1. Go to the meadow");
  tft.println("2. Go deeper into the forest");

  //Selections
  int buttonPressed = ButtonChoice();
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  boolean buttonPressReq = 0;
  switch (buttonPressed) {
    case 1:
      buttonPressReq = 1;
      state = meadow_1;
      break;
    case 2:
      buttonPressReq = 1;
      state = wolves_1;
      break;
  }
}

//Ghost Ship 1 *********************************************************************************************
void ghostShip_1() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 12; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(ghostShip1[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = ghostShip_2;
}

//Ghost Ship 2 *********************************************************************************************
void ghostShip_2() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 4; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(ghostShip2[i])));
    tft.println(buffer);
  }

  tft.drawLine(0, 245, 480, 245, TFT_WHITE);
  tft.setCursor(0, 250);
  tft.println("1. \"Malcolm, let's get out of here!\"");
  tft.println("2. \"Let's get a bit closer.\"");

  int buttonPressed = ButtonChoice();
  boolean buttonPressReq = 0;
  switch (buttonPressed) {
    case 1:
      buttonPressReq = 0;
      state = ghostShip_11;
      break;
    case 2:
      buttonPressReq = 0;
      state = ghostShip_3;
      break;
  }
}

//Ghost Ship 3 *********************************************************************************************
void ghostShip_3() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 6; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(ghostShip3[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = ghostShip_4;
}

//Ghost Ship 4 *********************************************************************************************
void ghostShip_4() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 9; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(ghostShip4[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = ghostShip_5;
}

//Ghost Ship 5 *********************************************************************************************
void ghostShip_5() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 10; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(ghostShip5[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = ghostShip_6;
}

//Ghost Ship 6 *********************************************************************************************
void ghostShip_6() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 11; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(ghostShip6[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = ghostShip_7;
}

//Ghost Ship 7 *********************************************************************************************
void ghostShip_7() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 9; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(ghostShip7[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = ghostShip_8;
}

//Ghost Ship 8 *********************************************************************************************
void ghostShip_8() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 14; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(ghostShip8[i])));
    tft.println(buffer);
  }

  //You pick up the cloak! Adds to inventory.
  haveCloak = 1;

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = ghostShip_9;
}

//Ghost Ship 9 *********************************************************************************************
void ghostShip_9() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 11; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(ghostShip9[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = ghostShip_10;
}

//Ghost Ship 10 *********************************************************************************************
void ghostShip_10() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 8; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(ghostShip10[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = townSquare_1;
}

//Ghost Ship 11 *********************************************************************************************
void ghostShip_11() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 9; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(ghostShip11[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = lighthouse_1;
}

//Hint *********************************************************************************************
void hint() {

  if (haveCloak == 0) {
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(0, 10);
    for (int i = 0; i < 2; i++) {
      strcpy_P(buffer, (char*)pgm_read_word(&(hint1[i])));
      tft.println(buffer);
    }
  } else if (haveOrb == 0) {
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(0, 10);
    for (int i = 0; i < 2; i++) {
      strcpy_P(buffer, (char*)pgm_read_word(&(hint2[i])));
      tft.println(buffer);
    }
  } else if (haveSword == 0) {
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(0, 10);
    for (int i = 0; i < 2; i++) {
      strcpy_P(buffer, (char*)pgm_read_word(&(hint3[i])));
      tft.println(buffer);
    }
  } else {
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(0, 10);
    for (int i = 0; i < 2; i++) {
      strcpy_P(buffer, (char*)pgm_read_word(&(hint4[i])));
      tft.println(buffer);
    }
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = chloe_1;
}

//Inventory 1 *********************************************************************************************
void inventory_1() {

  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  if (haveCloak == 1) {
    tft.println("You have the Cloak of Shadows");
  } else {
    tft.println("You don't have the Cloak of Shadows");
  }
  if (haveOrb == 1) {
    tft.println("You have the Starcaller Orb");
  } else {
    tft.println("You don't have the Starcaller Orb");
  }
  if (haveSword == 1) {
    tft.println("You have the Dragonbreaker sword");
  } else {
    tft.println("You don't have the Dragonbreaker sword");
  }
  tft.print("You have ");
  tft.print(water);
  tft.print(" liters of water");
  tft.setCursor(0, 160);
  tft.println("Note - Water is used in the desert");
  tft.println("at a rate of");
  tft.println(" > 2 liters per day");
  tft.println(" > 1 liters per night");
  tft.setCursor(160, 270);
  tft.println("press any key");

  int buttonPressed = ButtonChoice();
  state = townSquare_1;
}

//Lighthouse 1 *********************************************************************************************
void lighthouse_1() {

  //Recall Text from Flash
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 4; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(lighthouse1[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = lighthouse_2;
}

//Lighthouse 2 *********************************************************************************************
void lighthouse_2() {

  //Recall Text from Flash
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 9; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(lighthouse2[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = lighthouse_3;
}

//Lighthouse 3 *********************************************************************************************
void lighthouse_3() {

  //Recall Text from Flash
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 9; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(lighthouse3[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = dead;
}

//Lighthouse 4 *********************************************************************************************
void lighthouse_4() {

  //Recall Text from Flash
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 4; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(lighthouse4[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = lighthouse_5;
}

//Lighthouse 5 *********************************************************************************************
void lighthouse_5() {

  //Recall Text from Flash
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 8; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(lighthouse5[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = lighthouse_6;
}

//Lighthouse 6 *********************************************************************************************
void lighthouse_6() {

  //Recall Text from Flash
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 8; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(lighthouse6[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = lighthouse_7;
}

//Lighthouse 7 *********************************************************************************************
void lighthouse_7() {

  //Recall Text from Flash
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 9; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(lighthouse7[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = lighthouse_8;
}

//Lighthouse 8 *********************************************************************************************
void lighthouse_8() {

  //Recall Text from Flash
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 8; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(lighthouse8[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = lighthouse_9;
}

//Lighthouse 9 *********************************************************************************************
void lighthouse_9() {

  //Recall Text from Flash
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 12; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(lighthouse9[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = dead;
}

//Malcolm 1 *********************************************************************************************
void malcolm_1() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 12; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(malcolm1[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = malcolm_2;
}

//Malcom 2 *********************************************************************************************
void malcolm_2() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 9; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(malcolm2[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = malcolm_3;
}

//Malcolm 3 *********************************************************************************************
void malcolm_3() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 12; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(malcolm3[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = malcolm_4;
}

//Malcolm 4 *********************************************************************************************
void malcolm_4() {

  //Recall Text from Flash
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 10; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(malcolm4[i])));
    tft.println(buffer);
  }

  tft.drawLine(0, 245, 480, 245, TFT_WHITE);
  tft.setCursor(0, 250);
  tft.println("1.\"I see a pale blue light to port.\"");
  tft.println("2.\"I see a white light to starboard.\"");

  int buttonPressed = ButtonChoice();
  boolean buttonPressReq = 0;
  switch (buttonPressed) {
    case 1:
      buttonPressReq = 0;
      state = ghostShip_1;
      break;
    case 2:
      buttonPressReq = 0;
      state = lighthouse_4;
      break;
  }
}

//Meadow 1 ************************************************************************************************
void meadow_1() {

  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 11; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(meadow1[i])));
    tft.println(buffer);
  }

  tft.drawLine(0, 245, 480, 245, TFT_WHITE);
  tft.setCursor(0, 250);
  tft.println("1. Go to the cottage.");
  tft.println("2. Go to the pond.");

  int buttonPressed = ButtonChoice();
  boolean buttonPressReq = 0;
  switch (buttonPressed) {
    case 1:
      buttonPressReq = 0;
      state = witch_1;
      break;
    case 2:
      buttonPressReq = 0;
      state = pond_1;
      break;
  }
}

//Mountain 1 *********************************************************************************************
void mountain_1() {

  //Recall Text from Flash
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 9; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(mountain1[i])));
    tft.println(buffer);
  }

  tft.drawLine(0, 245, 480, 245, TFT_WHITE);
  tft.setCursor(0, 250);
  tft.println("1. Go back to town");
  tft.println("2. Go to the cave");

  int buttonPressed = ButtonChoice();
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  boolean buttonPressReq = 0;
  switch (buttonPressed) {
    case 1:
      buttonPressReq = 1;
      state = mountain_2;
      break;
    case 2:
      buttonPressReq = 1;
      state = tandirith_1;
      break;
  }
}

//Mountain 2 *********************************************************************************************
void mountain_2() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 2; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(mountain2[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = townSquare_1;
}

//Oasis 1 *********************************************************************************************
void oasis_1() {

  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  tft.println("OASIS!");


  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = dead;
}

//Pond 1 *********************************************************************************************
void pond_1() {

  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 9; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(pond1[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = pond_2;
}

//Pond 2 *********************************************************************************************
void pond_2() {

  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 10; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(pond2[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = witch_1;
}

//Scorpion 1 *********************************************************************************************
void scorpion_1() {

  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 9; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(scorpion1[i])));
    tft.println(buffer);
  }

  //Water meter
  tft.setCursor(0, 290);
  tft.print(water);
  tft.print(" liters of water");

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = scorpion_2;
}

//Scorpion 2 *********************************************************************************************
void scorpion_2() {

  if (haveOrb == 1) {
    water = water - 1;  //night water loss
  } else {
    water = water - 2;
  }

  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 11; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(scorpion2[i])));
    tft.println(buffer);
  }

  //Water meter
  tft.setCursor(0, 290);
  tft.print(water);
  tft.print(" liters of water");

  tft.drawLine(0, 245, 480, 245, TFT_WHITE);
  tft.setCursor(0, 250);
  tft.println("1. Go East to look for water");
  tft.println("2. Go West to look for water");
  tft.println("3. Go to the citadel tower (1-day)");

  int buttonPressed = ButtonChoice();
  boolean buttonPressReq = 0;
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  switch (buttonPressed) {
    case 1:
      tft.println("You wander to the East searching for.");
      tft.println("any sign of water.");
      tft.setCursor(160, 270);
      tft.println("press any key");
      buttonPressReq = 1;
      state = dead_thirst;
      break;
    case 2:
      tft.println("You wander to the West searching for.");
      tft.println("any sign of water.");
      tft.setCursor(160, 270);
      tft.println("press any key");
      buttonPressReq = 1;
      state = dead_thirst;
      break;
    case 3:
      tft.println("You leave the scorpion statue and begin");
      tft.println("walking in the direction of the distant");
      tft.println("tower.");
      tft.setCursor(160, 270);
      tft.println("press any key");
      buttonPressReq = 1;
      state = tower_1;
      break;
      if (buttonPressReq == 1) {
        int buttonPressed = ButtonChoice();
      }
  }
}

//Seamonster 1 *********************************************************************************************
void seamonster_1() {

  //Recall Text from Flash
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 12; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(seamonster1[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = seamonster_2;
}

//Seamonster 2 *********************************************************************************************
void seamonster_2() {

  //Recall Text from Flash
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 9; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(seamonster2[i])));
    tft.println(buffer);
  }

  tft.drawLine(0, 245, 480, 245, TFT_WHITE);
  tft.setCursor(0, 250);
  tft.println("1. Jump overboard and swim for shore");
  tft.println("2. Grab a harpoon");

  int buttonPressed = ButtonChoice();
  boolean buttonPressReq = 0;
  switch (buttonPressed) {
    case 1:
      buttonPressReq = 1;
      state = seamonster_3;
      break;
    case 2:
      buttonPressReq = 1;
      state = seamonster_6;
      break;
  }
}

//Seamonster 3 *********************************************************************************************
void seamonster_3() {

  //Recall Text from Flash
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 10; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(seamonster3[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = seamonster_4;
}

//Seamonster 4 *********************************************************************************************
void seamonster_4() {

  //Recall Text from Flash
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 7; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(seamonster4[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = seamonster_5;
}

//Seamonster 5 *********************************************************************************************
void seamonster_5() {

  //Recall Text from Flash
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 4; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(seamonster5[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = dead;
}

//Seamonster 6 *********************************************************************************************
void seamonster_6() {

  //Recall Text from Flash
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 12; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(seamonster6[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = seamonster_7;
}

//Seamonster 7 *********************************************************************************************
void seamonster_7() {

  //Recall Text from Flash
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 11; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(seamonster7[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = seamonster_8;
}

//Seamonster 8 *********************************************************************************************
void seamonster_8() {

  //Recall Text from Flash
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 7; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(seamonster8[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = lighthouse_1;
}

//Start 1 *********************************************************************************************
void start_1() {

  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 8; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(start1[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = start_2;
}

//Start 2 *****************************************************************************************
void start_2() {

  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 12; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(start2[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = start_3;
}

//Start 3 *****************************************************************************************
void start_3() {

  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 4; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(start3[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = start_4;
}

//Start  4 *****************************************************************************************
void start_4() {

  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 13; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(start4[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = start_5;
}

//Start 5 *****************************************************************************************
void start_5() {

  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 10; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(start5[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = start_6;
}

//Start 6 *****************************************************************************************
void start_6() {

  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  tft.println("You ask the man a question:");
  tft.drawLine(0, 245, 480, 245, TFT_WHITE);
  tft.setCursor(0, 250);
  tft.println("1. \"Where am I?\"");
  tft.println("2. \"Who are you?\"");
  tft.println("3. \"Who is the wizard?\"");
  tft.println("4. \"Can you take me to the wizard?\"");

  int buttonPressed = ButtonChoice();
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  boolean buttonPressReq = 0;
  switch (buttonPressed) {
    case 1:
      tft.fillScreen(TFT_BLACK);
      tft.setCursor(0, 10);
      for (int i = 0; i < 10; i++) {
        strcpy_P(buffer, (char*)pgm_read_word(&(start6_1[i])));
        tft.println(buffer);
      }
      tft.setCursor(160, 270);
      tft.println("press any key");
      buttonPressReq = 1;
      state = start_6;
      break;
    case 2:
      tft.fillScreen(TFT_BLACK);
      tft.setCursor(0, 10);
      for (int i = 0; i < 6; i++) {
        strcpy_P(buffer, (char*)pgm_read_word(&(start6_2[i])));
        tft.println(buffer);
      }
      tft.setCursor(160, 270);
      tft.println("press any key");
      buttonPressReq = 1;
      state = start_6;
      break;
    case 3:
      tft.fillScreen(TFT_BLACK);
      tft.setCursor(0, 10);
      for (int i = 0; i < 8; i++) {
        strcpy_P(buffer, (char*)pgm_read_word(&(start6_3[i])));
        tft.println(buffer);
      }
      tft.setCursor(160, 270);
      tft.println("press any key");
      buttonPressReq = 1;
      state = start_6;
      break;
    case 4:
      tft.fillScreen(TFT_BLACK);
      tft.setCursor(0, 10);
      for (int i = 0; i < 2; i++) {
        strcpy_P(buffer, (char*)pgm_read_word(&(start6_4[i])));
        tft.println(buffer);
      }
      tft.setCursor(160, 270);
      tft.println("press any key");
      buttonPressReq = 1;
      state = start_7;
      break;
  }
  if (buttonPressReq == 1) {
    int buttonPressed = ButtonChoice();
  }
}

//Start 7 *****************************************************************************************
void start_7() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 12; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(start7[i])));
    tft.println(buffer);
  }

  //Prompt
  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = start_8;
}

//Start 8 *****************************************************************************************
void start_8() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 6; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(start8[i])));
    tft.println(buffer);
  }

  //Prompt
  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = wizardHouse_1;
}

//Tandirith 1 *****************************************************************************************
void tandirith_1() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 15; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(tandirith1[i])));
    tft.println(buffer);
  }

  //Prompt
  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = tandirith_2;
}

//Tandirith 2 *****************************************************************************************
void tandirith_2() {

  //Recall Text from Flash
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 14; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(tandirith2[i])));
    tft.println(buffer);
  }

  tft.drawLine(0, 255, 480, 255, TFT_WHITE);
  tft.setCursor(0, 260);
  tft.println("1. Run!");
  if (haveCloak == 1) {
    tft.println("2. USE THE CLOAK OF SHADOWS");
  }
  int buttonPressed = ButtonChoice();
  boolean buttonPressReq = 0;
  switch (buttonPressed) {
    case 1:
      buttonPressReq = 1;
      state = tandirith_8;
      break;
    case 2:
      if (haveCloak == 1) {
        buttonPressReq = 1;
        state = tandirith_3;
      } else {
        state = tandirith_8;
      }
      break;
  }
}

//Tandirith 3 *****************************************************************************************
void tandirith_3() {

  //Recall Text from Flash
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 13; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(tandirith3[i])));
    tft.println(buffer);
  }

  tft.drawLine(0, 255, 480, 255, TFT_WHITE);
  tft.setCursor(0, 260);
  tft.println("1. Run!");
  if (haveOrb == 1) {
    tft.println("2. USE STARCALLER ORB");
  }
  int buttonPressed = ButtonChoice();
  boolean buttonPressReq = 0;
  switch (buttonPressed) {
    case 1:
      buttonPressReq = 1;
      state = tandirith_8;
      break;
    case 2:
      if (haveCloak == 1) {
        buttonPressReq = 1;
        state = tandirith_4;
      } else {
        state = tandirith_8;
      }
      break;
  }
}

//Tandirith 4 *****************************************************************************************
void tandirith_4() {

  //Recall Text from Flash
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 12; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(tandirith4[i])));
    tft.println(buffer);
  }

  tft.drawLine(0, 255, 480, 255, TFT_WHITE);
  tft.setCursor(0, 260);
  tft.println("1. Try to escape!");
  if (haveSword == 1) {
    tft.println("2. USE DRAGONBREAKER");
  }
  int buttonPressed = ButtonChoice();
  boolean buttonPressReq = 0;
  switch (buttonPressed) {
    case 1:
      buttonPressReq = 1;
      state = tandirith_9;
      break;
    case 2:
      if (haveCloak == 1) {
        buttonPressReq = 1;
        state = tandirith_5;
      } else {
        state = tandirith_9;
      }
      break;
  }
}

//Tandirith 5 *****************************************************************************************
void tandirith_5() {

  //Recall Text from Flash
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 10; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(tandirith5[i])));
    tft.println(buffer);
  }

  tft.drawLine(0, 255, 480, 255, TFT_WHITE);
  tft.setCursor(0, 260);
  tft.println("1. Attack with Dragonbreaker");
  if (haveCosmos == 1) {
    tft.println("2. WAIT FOR THE COSMOS TO SPEAK");
  }
  int buttonPressed = ButtonChoice();
  boolean buttonPressReq = 0;
  switch (buttonPressed) {
    case 1:
      buttonPressReq = 1;
      state = dead;
      break;
    case 2:
      if (haveCosmos == 1) {
        buttonPressReq = 1;
        state = tandirith_6;
      } else {
        state = dead;
      }
      break;
  }
}

//Tandirith 6 *****************************************************************************************
void tandirith_6() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 14; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(tandirith6[i])));
    tft.println(buffer);
  }

  //Prompt
  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = tandirith_7;
}

//Tandirith 7 *****************************************************************************************
void tandirith_7() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 11; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(tandirith7[i])));
    tft.println(buffer);
  }

  //Prompt
  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = ending_1;
}

//Tandirith 8 *****************************************************************************************
void tandirith_8() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 11; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(tandirith8[i])));
    tft.println(buffer);
  }

  //Prompt
  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = dead;
}

//Tandirith 9 *****************************************************************************************
void tandirith_9() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 11; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(tandirith9[i])));
    tft.println(buffer);
  }

  //Prompt
  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = dead;
}

//Tower 1
void tower_1() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 6; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(tower1[i])));
    tft.println(buffer);
  }
}

//Town Square 1 *********************************************************************************************
void townSquare_1() {

  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  tft.println("You are standing in the town square.");
  tft.println("What do you do?");

  tft.drawLine(0, 245, 480, 245, TFT_WHITE);
  tft.setCursor(0, 250);
  tft.println("1. Leave town");
  tft.println("2. Go to the wizard's house");
  tft.println("3. Check inventory");
  tft.println("4. Top off your water supply");

  int buttonPressed = ButtonChoice();
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  boolean buttonPressReq = 0;
  switch (buttonPressed) {
    case 1:
      buttonPressReq = 0;
      state = townSquare_2;
      break;
    case 2:
      tft.println("You go to the Wizard's house.");
      tft.setCursor(160, 270);
      tft.println("press any key");
      buttonPressReq = 1;
      state = chloe_1;
      break;
    case 3:
      tft.println("You take a look inside your pack.");
      tft.setCursor(160, 270);
      tft.println("press any key");
      buttonPressReq = 1;
      state = inventory_1;
      break;
    case 4:
      tft.println("You fill up your water bladder from");
      tft.println("the well in the town square.");
      tft.setCursor(160, 270);
      tft.println("press any key");
      buttonPressReq = 1;
      water = 5;
      previousWater = 5;
      state = townSquare_1;
      break;
  }
  if (buttonPressReq == 1) {
    int buttonPressed = ButtonChoice();
  }
}

//Town Square 2 *********************************************************************************************
void townSquare_2() {

  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  tft.println("By the corner of the square there is a");
  tft.println("sign post with directional arrows.");
  tft.println("It reads:");
  tft.println();
  tft.println("  > North to the Everwhite Mountains");
  tft.println("  > East to the Dark Forest");
  tft.println("  > South to the Burning Desert");
  tft.println("  > West to the Docks");
  tft.println();
  tft.println("Where do you go?");

  tft.drawLine(0, 245, 480, 245, TFT_WHITE);
  tft.setCursor(0, 250);
  tft.println("1. Go North");
  tft.println("2. Go East");
  tft.println("3. Go South");
  tft.println("4. Go West");

  int buttonPressed = ButtonChoice();
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  boolean buttonPressReq = 0;
  switch (buttonPressed) {
    case 1:
      tft.println("You head North for the Everwhite");
      tft.println("Mountains.");
      tft.setCursor(160, 270);
      tft.println("press any key");
      buttonPressReq = 1;
      state = mountain_1;
      break;
    case 2:
      if (haveOrb == 0) {
        tft.println("You head East for the Dark Forest.");
        tft.setCursor(160, 270);
        tft.println("press any key");
        buttonPressReq = 1;
        state = forest_1;
      } else {
        tft.println("I already have the orb. I need to go somewhere else.");
        tft.setCursor(160, 270);
        tft.println("press any key");
        buttonPressReq = 1;
        state = townSquare_2;
      }
      break;
    case 3:
      if (haveSword == 0) {
        tft.println("You head South for the Burning Desert.");
        tft.setCursor(160, 270);
        tft.println("press any key");
        buttonPressReq = 1;
        state = desert_1;
      } else {
        tft.println("I have all of the items. I should go visit Chloe at the wizard's house.");
        tft.setCursor(160, 270);
        tft.println("press any key");
        buttonPressReq = 1;
        state = townSquare_2;
      }
      break;
    case 4:
      if (haveCloak == 0) {
        tft.println("You head West to the docks.");
        tft.setCursor(160, 270);
        tft.println("press any key");
        buttonPressReq = 1;
        state = docks_1;
      } else {
        tft.println("I already have the cloak. I need to go somewhere else.");
        tft.setCursor(160, 270);
        tft.println("press any key");
        buttonPressReq = 1;
        state = townSquare_2;
      }
      break;
  }
  if (buttonPressReq == 1) {
    int buttonPressed = ButtonChoice();
  }
}

//Town Square 3 *********************************************************************************************
void townSquare_3() {

  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  tft.println("You are standing in the town square.");
  tft.println("What do you do?");

  tft.drawLine(0, 245, 480, 245, TFT_WHITE);
  tft.setCursor(0, 250);
  tft.println("1. Leave town");

  int buttonPressed = ButtonChoice();
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  boolean buttonPressReq = 0;
  switch (buttonPressed) {
    case 1:
      buttonPressReq = 0;
      state = townSquare_4;
      break;
  }
  if (buttonPressReq == 1) {
    int buttonPressed = ButtonChoice();
  }
}

//Town Square 4 *********************************************************************************************
void townSquare_4() {

  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  tft.println("By the corner of the square there is a");
  tft.println("sign post with directional arrows.");
  tft.println("It reads:");
  tft.println();
  tft.println("  > North to the Everwhite Mountains");
  tft.println("  > East to the Dark Forest");
  tft.println("  > South to the Burning Desert");
  tft.println("  > West to the Docks");
  tft.println();
  tft.println("You know where to go.");

  tft.drawLine(0, 245, 480, 245, TFT_WHITE);
  tft.setCursor(0, 250);
  tft.println("1. Go North");

  int buttonPressed = ButtonChoice();
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  boolean buttonPressReq = 0;
  switch (buttonPressed) {
    case 1:
      tft.println("You head North for the Everwhite Mountains.");
      tft.setCursor(160, 270);
      tft.println("press any key");
      buttonPressReq = 1;
      state = mountain_1;
      break;
  }
  if (buttonPressReq == 1) {
    int buttonPressed = ButtonChoice();
  }
}

//Witch 1 ************************************************************************************
void witch_1() {

  //Recall Text from Flash
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 9; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(witch1[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = witch_2;
}

//Witch 2 ************************************************************************************
void witch_2() {

  //Recall Text from Flash
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 9; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(witch2[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = witch_3;
}

//Witch 3 ************************************************************************************
void witch_3() {

  //Recall Text from Flash
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 8; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(witch3[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  if (haveCloak == 1) {
    state = witch_4;
  } else { 
    state = witch_8;
  }
}

//Witch 4 ************************************************************************************
void witch_4() {

  //Recall Text from Flash
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 12; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(witch4[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = witch_5;
}

//Witch 5 ************************************************************************************
void witch_5() {

  //Recall Text from Flash
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 10; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(witch5[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = witch_6;
}

//Witch 6 ************************************************************************************
void witch_6() {

  //Recall Text from Flash
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 9; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(witch6[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = witch_7;
}

//Witch 7 ************************************************************************************
void witch_7() {

  // reset inventory
  haveCloak = 0;
  haveOrb = 0;
  haveSword = 0;
  water = 0;
  previousWater = 0;

  //Recall Text from Flash
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 8; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(witch7[i])));
    tft.println(buffer);
  }

  tft.setCursor(0, 240);
  tft.println("Play Again?");
  tft.println(" ");
  tft.println("1. Start from Intro");
  tft.println("2. Skip Intro");
  int buttonPressed = ButtonChoice();
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  boolean buttonPressReq = 0;
  switch (buttonPressed) {
    case 1:
      buttonPressReq = 1;
      resetFunc();
      break;
    case 2:
      buttonPressReq = 1;
      state = townSquare_1;
      break;
  }
}

//Witch 8 ************************************************************************************
void witch_8() {

  //Recall Text from Flash
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 13; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(witch8[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = witch_9;
}

//Witch 9 ************************************************************************************
void witch_9() {

  //Recall Text from Flash
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 12; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(witch9[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = witch_7;
}

//Wizard House 1 *********************************************************************************************
void wizardHouse_1() {

  //Recall Text from Flash
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 2; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(wizardHouse1[i])));
    tft.println(buffer);
  }

  tft.drawLine(0, 245, 480, 245, TFT_WHITE);
  tft.setCursor(0, 250);
  tft.println("1. Knock on the door");
  tft.println("2. Go back to the town square");

  int buttonPressed = ButtonChoice();
  boolean buttonPressReq = 0;
  switch (buttonPressed) {
    case 1:
      buttonPressReq = 0;
      state = wizardHouse_2;
      break;
    case 2:
      buttonPressReq = 0;
      state = townSquare_1;
      break;
  }
  if (buttonPressReq == 1) {
    int buttonPressed = ButtonChoice();
  }
}

//Wizard House 2 ************************************************************************************
void wizardHouse_2() {

  //Recall Text from Flash
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 14; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(wizardHouse2[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = wizardHouse_3;
}

//Wizard House 3 ************************************************************************************
void wizardHouse_3() {

  //Recall Text from Flash
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 15; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(wizardHouse3[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = wizardHouse_4;
}

//Wizard House 4 ************************************************************************************
void wizardHouse_4() {

  //Recall Text from Flash
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 14; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(wizardHouse4[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = wizardHouse_5;
}

//Wizard House 5 ************************************************************************************
void wizardHouse_5() {

  //Recall Text from Flash
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 12; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(wizardHouse5[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = wizardHouse_6;
}

//Wizard House 6 ************************************************************************************
void wizardHouse_6() {

  //Recall Text from Flash
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 11; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(wizardHouse6[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = townSquare_1;
}

//Wolves 1 *********************************************************************************************
void wolves_1() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 14; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(wolves1[i])));
    tft.println(buffer);
  }

  tft.drawLine(0, 245, 480, 245, TFT_WHITE);
  tft.setCursor(0, 250);
  tft.println("1. Continue forward");
  tft.println("2. Go back to the fork");
  int buttonPressed = ButtonChoice();
  boolean buttonPressReq = 0;
  switch (buttonPressed) {
    case 1:
      buttonPressReq = 0;
      state = wolves_10;
      break;
    case 2:
      buttonPressReq = 0;
      state = wolves_10;
      break;
  }
}

//Wolves 2 *********************************************************************************************
void wolves_2() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 10; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(wolves2[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  if (haveCloak == 0) {
    int buttonPressed = ButtonChoice();
    state = wolves_3_1;
  } else {
    int buttonPressed = ButtonChoice();
    state = wolves_3_2;
  }
}

//Wolves 3 No Cloak *********************************************************************************************
void wolves_3_1() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 9; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(wolves3[i])));
    tft.println(buffer);
  }

  tft.drawLine(0, 245, 480, 245, TFT_WHITE);
  tft.setCursor(0, 250);
  tft.println("1. Prepare to fight!");
  tft.println("2. Run!");

  int buttonPressed = ButtonChoice();
  boolean buttonPressReq = 0;
  switch (buttonPressed) {
    case 1:
      buttonPressReq = 0;
      state = wolves_4;
      break;
    case 2:
      buttonPressReq = 0;
      state = wolves_6;
      break;
  }
  if (buttonPressReq == 1) {
    int buttonPressed = ButtonChoice();
  }
}

//Wolves 3 With Cloak *********************************************************************************************
void wolves_3_2() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 9; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(wolves3[i])));
    tft.println(buffer);
  }

  tft.drawLine(0, 245, 480, 245, TFT_WHITE);
  tft.setCursor(0, 250);
  tft.println("1. Prepare to fight!");
  tft.println("2. Run!");
  tft.println("3. USE THE CLOAK OF SHADOWS");

  int buttonPressed = ButtonChoice();
  boolean buttonPressReq = 0;
  switch (buttonPressed) {
    case 1:
      buttonPressReq = 0;
      state = wolves_4;
      break;
    case 2:
      buttonPressReq = 0;
      state = wolves_6;
      break;
    case 3:
      buttonPressReq = 0;
      state = wolves_7;
      break;
  }
  if (buttonPressReq == 1) {
    int buttonPressed = ButtonChoice();
  }
}

//Wolves 4 *********************************************************************************************
void wolves_4() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 11; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(wolves4[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = wolves_5;
}

//Wolves 5 *********************************************************************************************
void wolves_5() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 8; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(wolves5[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = dead;
}

//Wolves 6 *********************************************************************************************
void wolves_6() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 11; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(wolves6[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = dead;
}

//Wolves 7 *********************************************************************************************
void wolves_7() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 10; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(wolves7[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = wolves_8;
}

//Wolves 8 *********************************************************************************************
void wolves_8() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 17; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(wolves8[i])));
    tft.println(buffer);
  }

  //You pick up the Starcaller Orb! Adds to inventory.
  haveOrb = 1;

  tft.setCursor(160, 290);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = wolves_9;
}

//Wolves 9 *********************************************************************************************
void wolves_9() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 8; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(wolves9[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = townSquare_1;
}

//Wolves 10 *********************************************************************************************
void wolves_10() {

  //Text
  tft.fillScreen(TFT_BLACK);
  tft.setCursor(0, 10);
  for (int i = 0; i < 3; i++) {
    strcpy_P(buffer, (char*)pgm_read_word(&(wolves10[i])));
    tft.println(buffer);
  }

  tft.setCursor(160, 270);
  tft.println("press any key");
  int buttonPressed = ButtonChoice();
  state = meadow_1;
}
