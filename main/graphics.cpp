#include "graphics.h"

const int rs = 11;
const int en = 12;
const int d4 = 6;
const int d5 = 5;
const int d6 = 4;
const int d7 = 3;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void startLCD() {
  lcd.begin(16, 1);
  lcd.clear();
}

void displayInfo(char* info) {
  lcd.clear();
  lcd.print(info);
}
