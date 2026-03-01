// #include <Arduino.h>
// #include <U8g2lib.h>

// #ifdef U8X8_HAVE_HW_SPI
// #include <SPI.h>
// #endif
// #ifdef U8X8_HAVE_HW_I2C
// #include <Wire.h>
// #endif

//#define SENSOR 0

// U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
#include <LiquidCrystal.h>
const int rs = 11, en = 12, d4 = 6, d5 = 5, d6 = 4, d7 = 3; //initialize with LCD interface pins.
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);



void setup(void) {
  //u8g2.begin();
  setupSoil();
  lcd.begin(16, 1);
  // lcd.begin(16, 1);
  lcd.clear();
  lcd.print("Test");

  //startLCD();
}

void loop() {
  //helloWorld();
  getMoi();
  getDHT();
  
  //startLCD();
  //displayGraphic("Hello! :)");
  delay(2000);
}