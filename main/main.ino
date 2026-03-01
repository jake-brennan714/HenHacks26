#include "soil_hydrometer.h"
#include "graphics.h"
DHTPair* pair;
int moisture;
float score;
float oldScore;
char buffer[10];

void setup(void) {
  //u8g2.begin();
  setupSoil();
  score = 100;
  startLCD();
  
}

void loop() {
  //helloWorld();
  moisture = getMoi();
  pair = getDHT();
  oldScore = score;
  score = calculateState(oldScore, moisture, pair);
  Serial.println(score);
  dtostrf(score, 6, 2, buffer);
  displayInfo(buffer);
  delay(2000);
}