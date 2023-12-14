void menuUpdate(unsigned char encoderAction) {  //main menu navigation updater
  //called on by rotary encoder actions
  //parameter 0: no action from encoder
  //parameter 1: encoder click
  //parameter 2: encoder CW rotation
  //parameter 3: encoder CCW rotation

  //unsigned int verifiedMenuPos;

  if (encoderAction == 0) {
    //no action

  } else {  //triggered by action

    if (encoderAction == 1) {  //encoder click button

      //code below takes menu position to the next sub branch
      if (menuPos % 10 == 0) {  //if menu selection is at XX0 (zero at the end)
        menuPos = menuPos / 10; //go back up one level of menu (we use zero as the 'return' menu selection)
      } else {
        menuPos = menuPos * 10 + 1; //else, go further in one level of menu from the current selection
      }

      menuPos = menuVerifyPos(menuPos);
      menuAction(menuPos);  //click execution
      updateMenuDisplay(menuPos);

    } else if (encoderAction == 2) {  //encoder CW rotation

      if (menuPos % 10 == 9) {  //if current selection is at XX9
        //do nothing
      } else {
        menuPos ++;
      }

      menuPos = menuVerifyPos(menuPos);
      updateMenuDisplay(menuPos);


    } else if (encoderAction == 3) {  //encoder CCW rotation

      if (menuPos % 10 == 0) {  //if current selection is at XX0
        //do nothing
      } else {
        menuPos --;
      }

      menuPos = menuVerifyPos(menuPos);
      updateMenuDisplay(menuPos);
    }

    lastMenuPos = menuPos;

    //Serial.print("menuPos = ");
    //Serial.println(menuPos);

  }
}

void subMenu1Update(unsigned char encoderAction) { //sub menu type 1 updater: number selection 1 - 1000
  //called on by rotary encoder actions with a parameter to indicate:
  //parameter 0: no action from encoder
  //parameter 1: encoder click
  //parameter 2: encoder CW rotation
  //parameter 3: encoder CCW rotation

  if (encoderAction == 0) {

    // no action
  } else {

    if (encoderAction == 1) { //encoder click
      subMenuClick++;
      //Serial.print("subMenu1Update: click++; click = ");
      //Serial.println(subMenuClick);

      if (subMenuClick == 1) { //single click to exit sub menu
        lcd.clear();
        menuAction(lastMenuPos);   //calls menuAction with last main menu tree position
        return;
      }

    } else if (encoderAction == 2) {  //CW rotation
      if (interval >= 3000)
        interval = 3000;
      else
        interval += 1;

    } else if (encoderAction == 3) {  //CCW rotation

      if (interval <= 1)
        interval = 1;
      else
        interval -= 1;
    }

    //update 4th row of LCD to display sub menu position
    lcd.setCursor(0, 1);
    if (interval % 9 == 0 )
    {
      lcd.print("                ");
      lcd.setCursor(0, 1);
    }
    lcd.print(interval);
  }
}

void subMenu2Update(unsigned char encoderAction) { //sub menu type 1 updater: number selection 1 - 1000
  //called on by rotary encoder actions with a parameter to indicate:
  //parameter 0: no action from encoder
  //parameter 1: encoder click
  //parameter 2: encoder CW rotation
  //parameter 3: encoder CCW rotation

  if (encoderAction == 0) {

    // no action
  } else {

    if (encoderAction == 1) { //encoder click
      subMenuClick++;
      //Serial.print("subMenu1Update: click++; click = ");
      //Serial.println(subMenuClick);

      if (subMenuClick == 1) { //single click to exit sub menu
        lcd.clear();
        menuAction(lastMenuPos);   //calls menuAction with last main menu tree position
        return;
      }

    } else if (encoderAction == 2) {  //CW rotation
      if (microstep >= 0.0)
        microstep = 256;
      else
        microstep += microstep;

    } else if (encoderAction == 3) {  //CCW rotation

      if (microstep <= 1)
        microstep = 1;
      else
        microstep = microstep / 2;
    }

    //update 4th row of LCD to display sub menu position
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print(microstep);
    driver.microsteps(microstep);
  }
}

void subMenu3Update(unsigned char encoderAction) { //sub menu type 1 updater: number selection 0 - 255
  //called on by rotary encoder actions with a parameter to indicate:
  //parameter 0: no action from encoder
  //parameter 1: encoder click
  //parameter 2: encoder CW rotation
  //parameter 3: encoder CCW rotation

//  Serial.println("sub-menu 3 updated");
  int temp = 0;


  if (encoderAction == 0) {

    // no action
  } else {

    if (encoderAction == 1) { //encoder click
      subMenuClick++;
      //Serial.print("subMenu1Update: click++; click = ");
      //Serial.println(subMenuClick);

      if (subMenuClick == 1) { //single click to exit sub menu
        lcd.clear();
        menuAction(lastMenuPos);   //calls menuAction with last main menu tree position
        return;
      }

    } else if (encoderAction == 2) {  //CW rotation
      if (lightSettings[activeControl] >= 255)
        lightSettings[activeControl] = 255;
      else
        lightSettings[activeControl] += 1;

    } else if (encoderAction == 3) {  //CCW rotation

      if (lightSettings[activeControl] <= 0)
        lightSettings[activeControl] = 0;
      else
        lightSettings[activeControl] -= 1;
    }

    for (int i = 0; i < strip.numPixels(); i++) { // For each pixel in strip...
      strip.setPixelColor(i, lightSettings[1], lightSettings[2], lightSettings[3], lightSettings[4]);     //  Set pixel's color (in RAM)
    }
    strip.setBrightness(lightSettings[5]);
    strip.show();
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print(lightSettings[activeControl]);
  }
}
void subMenu4Update(unsigned char encoderAction) {
  Serial.print("subMenu4Update: encoderAction = ");
  Serial.println(encoderAction);

  if (encoderAction == 0) {
    Serial.println("subMenu4Update: No action");
    // No action
  } else {
    if (encoderAction == 1) { // Encoder click
      subMenuClick++;

      if (subMenuClick == 1) { // Single click to exit sub-menu
        lcd.clear();
        return;
      }
    } else if (encoderAction == 2 || encoderAction == 3) {  // CW or CCW rotation
      // Handle speed logic
      float increment = 0.5;

      if (encoderAction == 3) {  // CCW rotation
        increment = -increment;
      }

      if (speedInRPM + increment <= 100.0 && speedInRPM + increment >= 0.5) {
        speedInRPM += increment;
      }

      // Update LCD
      lcd.setCursor(0, 1);
      lcd.print("                ");
      lcd.setCursor(0, 1);
      lcd.print(speedInRPM);

      // Set motor speed
      setMotorSpeed(speedInRPM);
    }
  }
}





