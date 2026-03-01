#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <Arduino.h>
#include <LiquidCrystal.h>

// =====================
// LCD Pin Configuration
// =====================

extern const int rs;
extern const int en;
extern const int d4;
extern const int d5;
extern const int d6;
extern const int d7;

// =====================
// LCD Object
// =====================

extern LiquidCrystal lcd;

// =====================
// Function Prototypes
// =====================

void startLCD();
void helloWorld();

#endif