#include "soil_hydrometer.h"

DHTPair* pair;
int moisture;
float score;
float oldScore;

void setup(void) {
  //u8g2.begin();
  setupSoil();
  score = 100;
}

void loop() {
  //helloWorld();
  moisture = getMoi();
  pair = getDHT();
  oldScore = score;
  score = calculateState(oldScore, moisture, pair);
  Serial.println(score);
  delay(2000);
}