//Includes
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// Instances
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
Servo servo[6];

// Pins
byte pots[] = {A0, A1, A2, A3, A6, A7};
int servoPins[] = {3, 5, 6, 9, 10, 11};
#define SAVE 2
#define RESET 4
#define PLAY 7


// Joystick settings
int deadzone = 15;
int centers[] = {546, 542, 553, 549, 523, 493};

// Servos settings
int servoMin = 600;
int servoMax = 2400;
int servoRange = servoMax - servoMin;

// Speed weights
float weights[] = {10, 10, -10, -10, -10, -10};

// Position vars
float pos[] = {servoRange/2, servoRange/2, servoRange/2, servoRange/2, servoRange/2, servoRange/2, };

// increment smoothing
float incrs[] = {0, 0, 0, 0, 0, 0};
float tf = 0.2;
float tf_stop = 0.4;


// Motion Sequences
int stepDelay = 1; // minimum delay between steps (in ms per step)
int states[50][6];
int stateCount = 0;
bool playMode = false;
int playbackCount = 0;
