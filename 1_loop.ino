// Loop variables
int loopDelay = 10;
long int timer = millis();
int screenLoopDelay = 100;
long int timer2 = millis();



void loop()
{
  // Evaluate buttons
  if (digitalRead(SAVE) == LOW) {
    for (int i = 0; i < 6; i++)
    {
      // write positions to new slot
      states[stateCount][i] = pos[i];
    }
    stateCount++;

    saveState();

    // Debug
    Serial.println("Position saved");
    delay(400);

  }

  if (digitalRead(RESET) == LOW) {
    if (!playMode) {
      // delete stored states
      memset(states, 0, sizeof(states));
      stateCount = 0;

      resetStates();

      // Debug
      Serial.println("Reset!");
      delay(400);
    }
  }

  if (digitalRead(PLAY) == LOW) {
    // begin or stop playback sequence
    if (playMode) {
      exitPlayback();
    } else {
      initPlayback();
    }
    delay(400);
  }



  // Motion Algorithms
  if (playMode) {
    // We are doing a playback of the saved states

    // evaluate current move
    if (evaluateMove()) {

      // move was complete! Now setup new move or terminate
      if (playbackCount >= stateCount) {

        // increment move counter
        playbackCount++;

        // no more moves to play back
        exitPlayback();
      } else {

        // setup new move
        setupMove(playbackCount);

        delay(200); // remove

        // increment move counter
        playbackCount++;
      }
    }

  } else {
    // We can move freely around
    if (millis() - timer > loopDelay)
    {
      //update timer
      timer = millis();

      // read values
      readValues();

      // update servos
      servosWrite();
    }
  }


  // LCD Screen updater
  if (millis() - timer2 > screenLoopDelay)
  {
    //update timer
    timer2 = millis();

    // update display
    updateDisplay();
  }

}
