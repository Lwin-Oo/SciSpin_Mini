#include "Button2.h"
#include "Rotary.h"
#include <LiquidCrystal_I2C.h>

#define ROTARY_PIN1     5
#define ROTARY_PIN2     6
#define BUTTON_PIN      7

#define CLICKS_PER_STEP 4   // this number depends on your rotary encoder

LiquidCrystal_I2C lcd(0x27, 16, 2); // Updated for a 20x4 display

Rotary r;
Button2 b;

int menuIndex = 0; // Current menu item index

// Specify the custom order of menu items
const char *customOrder[] = {"SPIN", "STOP", "QUIT"};

void setup() {
  lcd.init();
  lcd.backlight();
  Serial.println("\n\nWELCOME");
  delay(50);
  r.begin(ROTARY_PIN1, ROTARY_PIN2, CLICKS_PER_STEP);
  r.setChangedHandler(rotate);
  r.setLeftRotationHandler(rotateRight);
  r.setRightRotationHandler(rotateLeft);

  b.begin(BUTTON_PIN);
  b.setTapHandler(click);
  b.setLongClickHandler(resetPosition);

  lcd.begin(20, 4); // Initialize the LCD with 20 columns and 4 rows
  lcd.print(customOrder[menuIndex]); // Display the initial menu item
}

void loop() {
  r.loop();
  b.loop();
}

// on change
void rotate(Rotary &r) {
  // Handle rotation
}

// on left rotation
void rotateLeft(Rotary &r) {
  lcd.clear(); // Clear the LCD screen

  // Increment menuIndex and wrap around if necessary
  menuIndex = (menuIndex - 1 + sizeof(customOrder) / sizeof(customOrder[0])) % (sizeof(customOrder) / sizeof(customOrder[0]));

  lcd.print(customOrder[menuIndex]); // Display the new menu item
  Serial.println("Selecting: " + String(customOrder[menuIndex]));
}

// on right rotation
void rotateRight(Rotary &r) {
  lcd.clear(); // Clear the LCD screen

  // Increment menuIndex and wrap around if necessary
  menuIndex = (menuIndex + 1) % (sizeof(customOrder) / sizeof(customOrder[0]));

  lcd.print(customOrder[menuIndex]); // Display the new menu item
  //Serial.println("Selecting: " + String(customOrder[menuIndex]));
}

// single click
void click(Button2 &btn) {
  lcd.clear(); // Clear the LCD screen
  lcd.print("Selected: " + String(customOrder[menuIndex])); // Display the selected menu item
  //Serial.println("Selected: " + String(customOrder[menuIndex]));
}

// long click
void resetPosition(Button2 &btn) {
  lcd.clear(); // Clear the LCD screen
  lcd.print("Reset Position");
  delay(1000);
  lcd.clear(); // Clear the LCD screen
  lcd.print(customOrder[menuIndex]); // Display the current menu item
  //Serial.println("Reset!");
}

















