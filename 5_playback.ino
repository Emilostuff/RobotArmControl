

// sequence variables
int goal[6];
int interval[6];
int step[6];
long int lastMove[6];
bool complete[6] = {1, 1, 1, 1, 1, 1};


void setupMove(int index) {

  // Debug
  Serial.print("Setting up move no: "); Serial.println(index);

  // Setup goal
  for (int i = 0; i < 6; i++)
  {
    goal[i] = states[index][i];
  }

  // reset status
  for (int i = 0; i < 6; i++)
  {
    complete[i] = false;
  }

  // calculate steps to move for each servo
  int dist[6];
  for (int i = 0; i < 6; i++)
  {
    dist[i] = goal[i] - pos[i];
  }

  // determine step direction
  for (int i = 0; i < 6; i++)
  {
    if (dist[i] >= 0) {
      step[i] = 1;
    } else {
      step[i] = -1;
    }
  }

  // determine duration (find move max steps)
  int stepMax = 0;
  int duration;
  for (int i = 0; i < 6; i++)
  {
    if (abs(dist[i]) > stepMax) {
      stepMax = abs(dist[i]);
    }
  }
  duration = stepMax * stepDelay;

  // calculate individual delays for servos:
  for (int i = 0; i < 6; i++)
  {
    interval[i] = round(float(duration) / float(abs(dist[i])));
  }


  // Setup starting point for timers:
  long int now = millis();
  for (int i = 0; i < 6; i++)
  {
    lastMove[i] = now;

    // check if any servo is already at goal
    if (pos[i] == goal[i]) {
      complete[i] = true;
    }
  }



  // Now we are ready to evaluate move...

}



bool evaluateMove() {
  long int now = millis();

  // make move if move is due
  for (int i = 0; i < 6; i++)
  {
    if (now - lastMove[i] >= interval[i] && complete[i] == false) {
      // reset timer
      lastMove[i] = now;

      // increment position
      pos[i] = pos[i] + step[i];

      // update servo
      write(i);

      // declare complete if goal has been met
      if (pos[i] == goal[i]) {
        complete[i] = true;
      }
    }
  }

  // check if all moves are complete
  for (int i = 0; i < 6; i++)
  {
    if (complete[i] == false) {
      return false;
    }
  }

  return true;
}



void initPlayback() {
  // Debug
  Serial.println("Playback started");

  playMode = true;

  // round values in posisiton array – to avoid ambiguity
  for (int i = 0; i < 6; i++)
  {
    pos[i] = round(pos[i]);
  }

  // capture number of states
  playbackCount = 0;

  // do some display stuff
  initDisplayPlay();

}

void exitPlayback() {
  // Debug
  Serial.println("Playback stopped");

  // pause briefly to display completion
  updateValues();
  delay(500);

  playMode = false;

  // reset active increments
  memset(incrs, 0, sizeof(incrs));

  // display stuff here
  initDisplay();
  playbackStop();
}
