void menuAction(unsigned int menuCode) {
  //gets called when rotary encoder is clicked,
  //check the current location inside the menu,
  //execute approriate actions
  //returns true if some action is executed
  //returns false if nothing is done
  //Serial.print("menuAction called with menuCode = ");
  //Serial.println(menuCode);

  switch (menuCode) {

    case 0:
      {
        motorReset();
      }
      break;

    case 111:  //set frame rpm
      if (subMenuActive != 1) {  //initialize the subMenu3

        lcd.clear();
        subMenuActive = 1;
        subMenuPos = 0;
        subMenuClick = 0;
        subMenu1Update(0); //calls subMenu3Update with 0 (no action)

      } else if (subMenuActive == 1) {  //already initialized

        subMenuActive = 0;  //deactivate submenu, activate main menu
        lcd.clear();
        menuPos = 11;
        updateMenuDisplay(menuPos);
        //code to set time variables
      }
      break;

    case 12:
      digitalWrite(EN_PIN, !digitalRead(EN_PIN));

      break;

    case 13:
      digitalWrite(DIR_PIN, !digitalRead(DIR_PIN));

      break;

    case 15:  // Speed Control submenu
      if (subMenuActive != 4) {  // initialize the Speed Control submenu
        lcd.clear();
        subMenuActive = 4;
        subMenuPos = 0;
        subMenuClick = 0;
        subMenu4Update(0);  // calls subMenu4Update with 0 (no action)
      } else if (subMenuActive == 4) {  // already initialized
        subMenuActive = 0;  // deactivate submenu, activate main menu
        lcd.clear();
        menuPos = 15;
        updateMenuDisplay(menuPos);
        setMotorSpeed(speedInRPM);
      }
      break;


    case 141:
      if (subMenuActive != 2) {  //initialize the subMenu3

        lcd.clear();
        subMenuActive = 2;
        subMenuPos = 0;
        subMenuClick = 0;
        subMenu2Update(0); //calls subMenu3Update with 0 (no action)

      } else if (subMenuActive == 2) {  //already initialized

        subMenuActive = 0;  //deactivate submenu, activate main menu
        lcd.clear();
        menuPos = 14;
        updateMenuDisplay(menuPos);
        //code to set time variables
      }
      break;

    case 151:
      if (subMenuActive != 3) {  //initialize the subMenu4

        lcd.clear();
        subMenuActive = 3;
        subMenuPos = 0;
        subMenuClick = 0;
        subMenu4Update(0); //calls subMenu4Update with 0 (no action)

      } else if (subMenuActive == 3) {  //already initialized

        subMenuActive = 0;  //deactivate submenu, activate main menu
        lcd.clear();
        menuPos = 15;
        updateMenuDisplay(menuPos);
        //code to set time variables
      }
      break;

    case 2210:
      activeControl = 1;
      if (subMenuActive != 3) {  //initialize the subMenu3

        lcd.clear();
        subMenuActive = 3;
        subMenuPos = 0;
        subMenuClick = 0;
        subMenu3Update(0); //calls subMenu3Update with 0 (no action)

      } else if (subMenuActive == 3) {  //already initialized

        subMenuActive = 0;  //deactivate submenu, activate main menu
        lcd.clear();
        menuPos = 22;
        updateMenuDisplay(menuPos);
        //code to set time variables
      }
      break;

    case 2221:
      activeControl = 2;
      if (subMenuActive != 3) {  //initialize the subMenu3

        lcd.clear();
        subMenuActive = 3;
        subMenuPos = 0;
        subMenuClick = 0;
        subMenu3Update(0); //calls subMenu3Update with 0 (no action)

      } else if (subMenuActive == 3) {  //already initialized

        subMenuActive = 0;  //deactivate submenu, activate main menu
        lcd.clear();
        menuPos = 22;
        updateMenuDisplay(menuPos);
        //code to set time variables
      }
      break;

    case 2231:
      activeControl = 3;
      if (subMenuActive != 3) {  //initialize the subMenu3

        lcd.clear();
        subMenuActive = 3;
        subMenuPos = 0;
        subMenuClick = 0;
        subMenu3Update(0); //calls subMenu3Update with 0 (no action)

      } else if (subMenuActive == 3) {  //already initialized

        subMenuActive = 0;  //deactivate submenu, activate main menu
        lcd.clear();
        menuPos = 22;
        updateMenuDisplay(menuPos);
        //code to set time variables
      }
      break;

    case 2241:
      activeControl = 4;
      if (subMenuActive != 3) {  //initialize the subMenu3

        lcd.clear();
        subMenuActive = 3;
        subMenuPos = 0;
        subMenuClick = 0;
        subMenu3Update(0); //calls subMenu3Update with 0 (no action)

      } else if (subMenuActive == 3) {  //already initialized

        subMenuActive = 0;  //deactivate submenu, activate main menu
        lcd.clear();
        menuPos = 22;
        updateMenuDisplay(menuPos);
        //code to set time variables
      }
      break;

    case 23:
      activeControl = 5;
      if (subMenuActive != 3) {  //initialize the subMenu3

        lcd.clear();
        subMenuActive = 3;
        subMenuPos = 0;
        subMenuClick = 0;
        subMenu3Update(0); //calls subMenu3Update with 0 (no action)

      } else if (subMenuActive == 3) {  //already initialized

        subMenuActive = 0;  //deactivate submenu, activate main menu
        lcd.clear();
        menuPos = 23;
        updateMenuDisplay(menuPos);
        //code to set time variables
      }
      break;


    case 3:  //reset
      {
        motorReset();
      }
      break;

    case 4:  //save
      {
        saveSettings();
      }
      break;
  }
}
