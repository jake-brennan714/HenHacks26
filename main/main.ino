#include "soil_hydrometer.h"
#include "graphics.h"
#include "joystick.h"
DHTPair* pair;
int moisture;
float score;
float oldScore;
char buffer[10];
char name[11];
//int nameNum[11] = {0};
bool isRunning;
int menu;
const int NAME_LEN = 11;

const int CENTER = 500;      // joystick center ~500
const int DEAD   = 200;      // deadzone radius (try 80-200)

const unsigned long REPEAT_MS        = 140;  // hold-to-repeat rate for joystick
const unsigned long BLINK_INTERVALMS = 400;  // blink speed

int loc = 0;                 // selected position (0..10)
int nameNum[NAME_LEN] = {0}; // character indices (can be +/-)

// timing
unsigned long lastRepeat = 0;
unsigned long lastBlink  = 0;
bool showChar = true;


void setup(void) {
  //u8g2.begin();
  
  initJoystick();

  setupSoil();
  score = 100;
  isRunning = false;
  startLCD();
  menu = 1;
  
}

void updateNameEntry() {
  // Read joystick (0..1023)
  int x = pollX();
  int y = pollY();

  // Determine directions relative to center
  bool xUp = x > (CENTER + DEAD);
  bool xDown  = x < (CENTER - DEAD);
  bool yRight    = y < (CENTER - DEAD);
  bool yLeft  = y > (CENTER + DEAD);

  unsigned long now = millis();

  // --- Hold-to-repeat movement/editing ---
  if (now - lastRepeat >= REPEAT_MS) {
    bool didSomething = false;

    // Move selection
    if (yRight) { loc = (loc + 1) % NAME_LEN; didSomething = true; }
    else if (yLeft) { loc = (loc + NAME_LEN - 1) % NAME_LEN; didSomething = true; }

    // Change selected character
    if (xUp) { nameNum[loc]++; didSomething = true; }
    else if (xDown) { nameNum[loc]--; didSomething = true; }

    if (didSomething) lastRepeat = now;
  }

  // --- Blink selected letter (non-blocking) ---
  if (now - lastBlink >= BLINK_INTERVALMS) {
    showChar = !showChar;
    lastBlink = now;
  }

  // --- Draw 11 characters, blink the selected one ---
  for (int i = 0; i < NAME_LEN; i++) {
    if (i == loc && !showChar) {
      writeCharToLoc(' ', i, 1);   // hide selected char
      // or writeCharToLoc('_', i, 1); // alternate blink style
    } else {
      writeCharToLoc(getChar(nameNum[i]), i, 1);
    }
  }
}

void loop() {
  
  clear();

  if (isRunning) {
    moisture = getMoi();
    pair = getDHT();
    oldScore = score;
    score = calculateState(oldScore, moisture, pair);
    Serial.println(score);
    dtostrf(score, 6, 2, buffer);
    //displayInfo(buffer);
    char line[20];
  snprintf(line, sizeof(line), "%s's HP:", name);
  displayInfo(line);
    makeBar(score);
    delay(2000);
  }

  if (menu == 1) {
    displayInfo("Name your plant", 0, 0);
    while (pollB()) {
      updateNameEntry();
    }
      for (int i = 0; i < NAME_LEN; i++) {
      name[i] = getChar(nameNum[i]);
    }
    name[NAME_LEN - 1] = '\0'; // Null terminate so it's a proper C-string
    menu = 0;
    isRunning = true;
  }
}