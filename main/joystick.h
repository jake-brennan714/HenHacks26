//int ledPin = 13;
#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <Arduino.h>
extern int joyX;                 // slider variable connected to analog pin 1
extern int joyY;                 // slider variable connected to analog pin 2
extern int joyBtn;
extern int value1;                  // variable to read the value from the analog pin 0
extern int value2;                  // variable to read the value from the analog pin 1

void initJoystick();

#endif