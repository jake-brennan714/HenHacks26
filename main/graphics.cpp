#include "graphics.h"
#include <Arduino.h>
#include <LiquidCrystal.h>



const int rs = 11;
const int en = 12;
const int d4 = 6;
const int d5 = 5;
const int d6 = 4;
const int d7 = 3;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void startLCD() {
  lcd.begin(16, 2);
  lcd.clear();
}

void displayInfo(char* info, int x = 0, int y = 0) {
  //lcd.clear();
  lcd.setCursor(x,y);
  lcd.print(info);
}

void makeBar(float percentFilled) {
  percentFilled = constrain(percentFilled, 0.0f, 100.0f);
  lcd.setCursor(0,1);
  lcd.write('[');
  lcd.setCursor(15,1);
  lcd.write(']');
  int barsFilled = round((percentFilled/ 100.0f) * 14);
  for (int i = 0; i < barsFilled; i++) {
    lcd.setCursor(i+1, 1);
    lcd.write(0xfc);
  }
}

void clear() {
  lcd.clear();
}

char getChar(int index) {
    static const char chars[] =
    "_abcdefghijklmnopqrstuvwxyz"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "0123456789 ";

    const int size = 64;

    int wrapped = ((index % size) + size) % size;
    return chars[wrapped];
}

void writeCharToLoc(char charater, int x, int y) {
  lcd.setCursor(x, y);
  lcd.write(charater);
}
