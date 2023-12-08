#include "Button2.h"
#include "Rotary.h"
#include <LiquidCrystal_I2C.h>

#define ROTARY_PIN1     5
#define ROTARY_PIN2     6
#define BUTTON_PIN      7

#define CLICKS_PER_STEP 4 

LiquidCrystal_I2C lcd(0x27, 16, 2);

Rotary r;
Button2 b;

const char circle[] = {
  B00100,
  B01010,
  B10001,
  B10001,
  B01010,
  B00100
};

int menuIndex = 0;
int rotationAngle = 0;

const char *customOrder[] = {"SPIN", "STOP", "QUIT"};

void setup() {
  lcd.init();
  lcd.backlight();
  displayWelcomeAnimation(); // Display a fancy welcome message
  delay(2000); // Display for 2 seconds
  lcd.clear();

  r.begin(ROTARY_PIN1, ROTARY_PIN2, CLICKS_PER_STEP);
  r.setChangedHandler(rotate);
  r.setLeftRotationHandler(rotateRight);
  r.setRightRotationHandler(rotateLeft);

  b.begin(BUTTON_PIN);
  b.setTapHandler(click);
  //b.setLongClickHandler(resetPosition);

  lcd.println(" Spinner Menu ");
  lcd.print(customOrder[menuIndex]);
}

void loop() {
  r.loop();
  b.loop();
}

void rotate(Rotary &r) {
  // Handle rotation
}

void rotateLeft(Rotary &r) {
  menuIndex = (menuIndex - 1 + sizeof(customOrder) / sizeof(customOrder[0])) % (sizeof(customOrder) / sizeof(customOrder[0]));
  lcd.clear();
  lcd.print(customOrder[menuIndex]);
}

void rotateRight(Rotary &r) {
  menuIndex = (menuIndex + 1) % (sizeof(customOrder) / sizeof(customOrder[0]));
  lcd.clear();
  lcd.print(customOrder[menuIndex]);
}

void click(Button2 &btn) {
  lcd.clear();
  if (String(customOrder[menuIndex]) == "SPIN") {
    
    lcd.print("Motor Spinning");
    

  } else if (String(customOrder[menuIndex]) == "STOP") {
    lcd.print("Motor Stopped");
  } else if (String(customOrder[menuIndex]) == "QUIT") {
    displayGoodbyeAnimation();
    delay(2000); // Display the animation for 2 seconds
    lcd.noBacklight(); // Turn off the LCD backlight
    delay(1000); // Keep the LCD turned off for 1 second
    lcd.backlight(); // Turn on the LCD backlight
    lcd.clear();
    displayWelcomeAnimation();
    delay(2000); // Display "Welcome" for 2 seconds
    //lcd.clear();
    //menuIndex = 0;
  }
}

//void resetPosition(Button2 &btn) {
  //lcd.clear();
  //lcd.print("Reset Position");
  //delay(1000);
  //lcd.clear();
  //lcd.print(customOrder[menuIndex]);
//}

void displayWelcomeAnimation() {
  lcd.clear();

  // Display a simple animation loop
  for (int i = 0; i < 10; ++i) {
    lcd.setCursor(i, 1);
    lcd.print("CoSE");
    delay(200);
    lcd.clear();
  }
}

void displayGoodbyeAnimation() {
  lcd.clear();

  // Display a goodbye animation loop
  for (int i = 0; i < 3; ++i) {
    lcd.setCursor(i, 1);
    lcd.print("+");
    delay(500);
    lcd.clear();
  }
}

















