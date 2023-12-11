//_______________________________ LIBRARIES ________________________________//
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>
#include <Adafruit_NeoPixel.h>
#include <TMC2208Stepper.h>

#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif

//________________________________ Constants for pin assignments ________________________________//
const int ROTARY_PIN_A = 5; // CLK
const int ROTARY_PIN_B = 6; // DT
const int ROTARY_BUTTON_PIN = 7;
const int EN_PIN = 9;
const int STEP_PIN = 11;
const int RX_PIN = 10;
const int TX_PIN = 8;
const int DIR_PIN = 12;
const int BUZZER_PIN = 13;
const int LED_PIN = 3;
const int LED_COUNT = 60;

//________________________________ Other constants ________________________________//
const int INTERVAL_DEFAULT = 200;
const int CURRENT_LIMIT_DEFAULT = 600;
const int MICROSTEP_DEFAULT = 256;
const int MENU_UPDATE_INTERVAL = 200;

//________________________________ Function Prototypes ________________________________//
void initializePeripherals(); 
void motorReset();
void readSettings();
void saveSettings();
void beep();
void longBeep();
void startup();
void colorWipe(uint32_t c, uint8_t wait);
void menuAction(unsigned int menuCode);
void menuUpdate(unsigned char encoderAction);
void subMenu1Update(unsigned char encoderAction);
void subMenu2Update(unsigned char encoderAction);
void subMenu3Update(unsigned char encoderAction);
void numericalSubMenuUpdate(unsigned char encoderAction, int& value, int minValue, int maxValue); 
void clearAndSetCursor(int row, int col);

//________________________________ Global Variables ________________________________//

//1. Encoder Variables
unsigned long currentTime;   // Current time variable
unsigned long loopTime;      // Time variable for loop execution timing
unsigned char encoder_A = 0; // State variable for encoder pin A
unsigned char encoder_B = 0; // State variable for encoder pin B
unsigned char encoder_C = 1; // State variable for encoder button (encoder push button)
unsigned char encoder_A_prev = 0; // Previous state variable for encoder pin A
unsigned char encoder_C_prev = 1; // Previous state variable for encoder button

//2. Menu Variables
unsigned int maxMenuItems;     // Maximum number of menu items
unsigned int menuPos = 0;      // Current menu position
unsigned int lastMenuPos = 0;  // Previous menu position
unsigned int parentMenuPos = 0; // Parent menu position
bool humanInputActive = false;  // Flag to indicate if input session is active
unsigned int subMenuActive = 0;   // Flag to indicate a sub-selection menu session is active (0 - main menu; 1 - number selection 1-255; 2 - binary selection yes/no; 3 - time setting;)
unsigned int subMenuPos = 0;    // Sub-menu rotary position
unsigned int subMenuClick = 0;  // Sub-menu click counter
unsigned long CurrentTimeS;     // Current time (start)
unsigned long CurrentTimeE;     // Current time (end)

//2. LED Variables
int lightSettings[6] = {0,100, 0, 0, 0, 50};
int activeControl = 0;

//2. Motor Variables
int interval = 200;
int currentLimit = 600;
int microstep = 256;
unsigned long NextTime = 0;

//________________________________ Define the menu item structure ________________________________//
struct MenuItem {
  unsigned int code;
  const char* text;
};

const int MAX_MENU_ITEMS = 25;

MenuItem menu[MAX_MENU_ITEMS];


//________________________________ Define the display ________________________________//
LiquidCrystal_I2C lcd(0x27, 16, 2);

//________________________________ Define the motor ________________________________//
TMC2208Stepper driver = TMC2208Stepper(RX_PIN, TX_PIN);

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);

void setup(){
  Serial.begin(9600);
  Wire.begin();
  //rotaryEncoderInit();
  menuInit();

  lcd.init();
  lcd.backlight();
  
  lcd.setCursor(1, 0);
  lcd.print("COSE CLINOSTAT");

  lcd.setCursor(5, 1);
  lcd.print("V 1.02");

  pinMode(ROTARY_PIN_A, INPUT_PULLUP);
  pinMode(ROTARY_PIN_B, INPUT_PULLUP);
  pinMode(ROTARY_BUTTON_PIN, INPUT_PULLUP); 

  pinMode(BUZZER_PIN, OUTPUT);

  driver.beginSerial(115200);
   driver.push();
  // Prepare pins
  pinMode(EN_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);

  driver.pdn_disable(true);     // Use PDN/UART pin for communication
  driver.I_scale_analog(false); // Use internal voltage reference
  driver.rms_current(currentLimit);      // Set driver current = 500mA, 0.5 multiplier for hold current and RSENSE = 0.11.
  driver.toff(2);               // Enable driver in software
  driver.mstep_reg_select(true);
  driver.microsteps(microstep);
  driver.dedge(true);

  digitalWrite(EN_PIN, HIGH);    // Enable driver in hardware

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(lightSettings[6]);

  motorReset();
  startup();

}

void loop() {
  //  CurrentTimeS = micros();
  rotaryEncoderUpdate();

  if (micros() < NextTime)
    NextTime = micros();

  if (micros() - NextTime > interval) {
    digitalWrite(STEP_PIN, !digitalRead(STEP_PIN));
    NextTime = micros();         // reset for next pulse
  }

}

void rotaryEncoderInit() {
  currentTime = millis();
  loopTime = currentTime;  
}

void rotaryEncoderUpdate() {

  //rotary encoder update, to be called from main loop()

  currentTime = millis();
  if (currentTime >= (loopTime + 1) ) {
    encoder_A = digitalRead(ROTARY_PIN_A);
    encoder_B = digitalRead(ROTARY_PIN_B);
    encoder_C = digitalRead(ROTARY_BUTTON_PIN);

    //handling knob rotation
    if ( (encoder_A == 0) && (encoder_A_prev == 1) ) {  //encoder changed position
      beep();

      if (encoder_B == 1) { //B is high, so encoder moved clockwise
        //Serial.println("encoder rotated CW");

        switch (subMenuActive) { //send encoder action to appropriate menu handler
          case 0: //main menu
            menuUpdate(2);
            break;

          case 1: //subMenu1
            subMenu1Update(2);
            break;

          case 2: //subMenu1
            subMenu2Update(2);
            break;

          case 3: //subMenu1
            subMenu3Update(2);
            break;

          default:
            menuUpdate(2);
            break;
        }


      } else {  //else, encoder moved counter-clockwise
        //Serial.println("encoder rotated CCW");

        switch (subMenuActive) {  //call the appropriate menuupdater depending on which sub menu is active
          case 0:
            menuUpdate(3);
            break;

          case 1:
            subMenu1Update(3);
            break;

          case 2: //subMenu1
            subMenu2Update(3);
            break;

          case 3: //subMenu1
            subMenu3Update(3);
            break;

          default:
            menuUpdate(3);
            break;
        }
      }

    }

    //handling push button
    if ( (encoder_C == 0) && (encoder_C_prev == 1) ) { //button pushed
      //Serial.println("encoder button closed.");
      longBeep();
      switch (subMenuActive) {  //call the appropriate menuupdater depending on which sub menu is active
        case 0:
          menuUpdate(1);
          break;

        case 1:
          subMenu1Update(1);
          break;

        case 2: //subMenu1
          subMenu2Update(1);
          break;

        case 3: //subMenu1
          subMenu3Update(1);
          break;

        default:
          menuUpdate(1);
          break;
      }

    } else if ( (encoder_C == 1) && (encoder_C_prev == 0) )  {  //button
      //Serial.println("encoder button opened.");

    }

    encoder_A_prev = encoder_A;
    encoder_C_prev = encoder_C;
    loopTime = currentTime;

  }

}



unsigned int menuVerifyPos(unsigned int menuCode) {
  //accepts a code that represents position in the menu
  //checks against the menu, verify it exist, and returns it
  //if the menu code given does not exist,
  //returns the closest code smaller than the one given

  bool confirmCode = false; //flag to keep track of whether code has been confirmed in menu tree

  for (unsigned int k = 0; k <= (maxMenuItems - 1); k++) {

    if (menuCode == menu[k].code) {  //found exact code, returns it
      menuPos = menu[k].code;
      confirmCode = true;
      lastMenuPos = menuCode;
      return menuPos;
    }

  }

  if (confirmCode == false) {
    menuPos = lastMenuPos;
    return menuPos;   //cannot find menu option, go back to previous menu option
  }

}

void updateMenuDisplay(unsigned int menuCode) {
  //prints menu selection to the LCD display
  //in order to have a scrolling menu effect, this code looks at item before and after current menu item and display them in a row


  String curMenu;
  String nextMenu;

  curMenu = findMenuTextFromCode(menuCode);
  nextMenu = findMenuTextFromCode((menuCode + 1));

  //starts printing to LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.printByte(1);
  //char index, row index, on LCD
  lcd.print(curMenu);

  lcd.setCursor(1, 1);
  lcd.print(nextMenu); //print the next menu text in the 3rd row
}

String findMenuTextFromCode(unsigned int menuCode) {
  //accepts a code representing the code in menu, and returns the corresponding text

  for (unsigned int j = 0; j <= (maxMenuItems - 1); j++ ) {
    if (menuCode == menu[j].code) {
      return menu[j].text;
      break;
    }
  }
}
















