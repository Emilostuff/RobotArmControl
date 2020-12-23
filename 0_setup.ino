
void setup()
{
  // Serial for debug
  Serial.begin(9600);

  // LCD Setup
  lcd.begin(20, 4);              // initialize the lcd
  initDisplay();
  updateDisplay();

  uint8_t testChar[8] = {0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff}; // Custom char
  lcd.createChar(0, testChar); // Sends the custom char to lcd


  // Pin setup
  for (int i = 0; i < 6; i++)
  {
    pinMode(pots[i], INPUT_PULLUP);
  }
  pinMode(SAVE, INPUT_PULLUP); 
  pinMode(RESET, INPUT_PULLUP);
  pinMode(PLAY, INPUT_PULLUP);

  // Attacch servos
  for (int i = 0; i < 6; i++)
  {
    servo[i].attach(servoPins[i], servoMin, servoMax);
  }







}
