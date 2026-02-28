#define SENSOR 0

//void setup() {
  // put your setup code here, to run once:
  //Serial.begin(57600);
//}

//void loop() {
  // put your main code here, to run repeatedly:
  //Serial.print("Moisture Sensor Value:");
  //Serial.println(analogRead(SENSOR));
  //delay(100);
//}

void setupSoil() {
  Serial.begin(57600);
}

void getMoi() {
  Serial.print("Moisture Sensor Value:");
  Serial.println(analogRead(SENSOR));
  delay(100);
}