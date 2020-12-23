// timer for displaying messages
long int messageTimer = millis();
int mesDur = 1500;
bool message = false;



void updateDisplay () {

  // Check if message timer has run out
  if (message && !playMode) {
    if (millis() - messageTimer >= mesDur) {
      // Timer has run out – go back to normal display
      initDisplay ();
      message = false;
    }
  }

  // Update position values
  updateValues();

}


void initDisplay () {

  lcd.home();
  lcd.clear();

  // Write labels
  lcd.setCursor (0, 2);
  lcd.print ("Rot");

  lcd.setCursor (4, 2);
  lcd.print ("1st");

  lcd.setCursor (8, 2);
  lcd.print ("2nd");

  lcd.setCursor (12, 2);
  lcd.print ("3rd");

  lcd.setCursor (16, 2);
  lcd.print ("Piv");

  lcd.setCursor (4, 0);
  lcd.print ("Gripper:");

}

void initDisplayPlay() {
  lcd.clear();

  // Write labels
  lcd.setCursor (0, 0);
  lcd.print ("Playback running ...");

  lcd.setCursor (3, 2);
  lcd.print ("Progress:");


}

void updateValues () {

  if (playMode) {
    // clear
    lcd.setCursor (13, 2);
    lcd.print ("       ");

    // print percentage
    int prog = int(100*float(playbackCount-1) / float(stateCount));

    lcd.setCursor (13, 2);

    if (prog < 10) {
      lcd.print (prog);
      lcd.setCursor (15, 2);
      lcd.print ("%");
    } else if (prog < 100) {
      lcd.print (prog);
      lcd.setCursor (16, 2);
      lcd.print ("%");
    } else {
      lcd.print (prog);
      lcd.setCursor (17, 2);
      lcd.print ("%");
    }

    // Set progress bar
    int bars = int(float(20)*float(prog)/100.0);

    for (int i = 0; i < bars; i++) {
      lcd.setCursor (i, 3);
      lcd.print((char)0);
    }



  } else {
    // clear
    lcd.setCursor (0, 3);
    lcd.print ("                    ");

    for (int i = 0; i < 5; i++) {
      lcd.setCursor (i * 4, 3);
      lcd.print (int(pos[i] / 10));
    }

    // update gripper as well
    updateGripper();

  }
}

void updateGripper () {
  // clear
  if (!message) {
    lcd.setCursor (13, 0);
    lcd.print ("    ");

    lcd.setCursor (13, 0);
    lcd.print (int(pos[5] / 10));
  }
}

void newMessage () {
  // set timer
  messageTimer = millis();
  message = true;

  // clear top rows
  lcd.setCursor (0, 0);
  lcd.print ("                    ");
  lcd.setCursor (0, 1);
  lcd.print ("                    ");
}

void saveState () {

  // set message state
  newMessage();

  // print message
  lcd.setCursor (2, 0);
  lcd.print ("Position stored!");
}

void resetStates () {

  // set message state
  newMessage();

  // print message
  lcd.setCursor (2, 0);
  lcd.print ("Memory cleared!");

}

void playbackStop () {

  // set message state
  newMessage();

  // print message
  lcd.setCursor (2, 0);
  lcd.print ("Playback stopped!");
}
