#include "joystick.h"

int joyX;
int joyY;
int joyBtn;
int value1;
int value2;

void initJoystick() {
  
  Serial.begin(9600);
  pinMode(joyBtn, INPUT_PULLUP);

  joyX = A1;
  joyY = A2;
  joyBtn = A3;

  value1 = 0;
  value2 = 0;
}