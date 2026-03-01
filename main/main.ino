#include "soil_hydrometer.h"
#include "graphics.h"
#include "joystick.h"
DHTPair* pair;
int moisture;
float score;
float oldScore;
char buffer[10];




void setup(void) {
  //u8g2.begin();
  
  initJoystick();

  setupSoil();
  score = 100;
  startLCD();
  
}

void loop() {
  //helloWorld();
  int xValue = analogRead(joyX);
  int yValue = analogRead(joyY);
  int btnState = digitalRead(joyBtn);
  Serial.print("X: ");
  Serial.print(xValue);
  Serial.print(" | Y: ");
  Serial.print(yValue);
  Serial.print(" | Button: ");
  Serial.println(btnState);


  moisture = getMoi();
  pair = getDHT();
  oldScore = score;
  score = calculateState(oldScore, moisture, pair);
  Serial.println(score);
  dtostrf(score, 6, 2, buffer);
  displayInfo(buffer);
  makeBar(score);
  delay(2000);

}