#include "Adafruit_Sensor.h"
#include "DHT.h"

#define HYDROMETER 0
#define DHTPIN 2

#define DHTTYPE DHT11

DHT dht = DHT(DHTPIN, DHTTYPE);

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
  // Serial.begin(57600);
  Serial.begin(9600);

  dht.begin();
}

void getMoi() {
  Serial.print("Moisture Sensor Value:");
  Serial.println(analogRead(HYDROMETER));
}

void getDHT() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("DHT Sensor Values: Humidity: ");
  Serial.print(h);
  Serial.print("; Temperature (\xC2\xB0");
  Serial.print("C): ");
  Serial.println(t);
}

int calculateState(int prevState, int soil_moisture,
float air_humidity, float air_temp) {
  int state = prevState;
  if (soil_moisture < 300) {
    // Soil is dry.
  } else if (soil_moisture > 700) {
    // Soil is oversaturated
  } else {
    // Soil is humid
  }

  // Standard humidity preferences
  if (air_humidity < 40.0f) {
    // Air is too arid
  } else if (air_humidity > 70.0f) {
    // Air is too humid
  } else {
    // Air is just right
  }

  // Standard temp preferences
  if (air_temp < 13.0f) {
    // Air too cold
  } else if (air_temp > 27.0f) {
    // Air too hot
  } else {
    // Air just right
  }
}