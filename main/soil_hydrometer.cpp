#include "soil_hydrometer.h"

DHTPair* getDHT();
float calculateState(float prev_state, int soil_moisture, DHTPair* dhtp);

#include "Adafruit_Sensor.h"
#include "DHT.h"

#define MOISTURE_WEIGHT 0.5
#define TEMPERATURE_WEIGHT 0.3
#define HUMIDITY_WEIGHT 0.2

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

int getMoi() {
  // Serial.print("Moisture Sensor Value:");
  // Serial.println(analogRead(HYDROMETER));
  return analogRead(HYDROMETER);
}

DHTPair* getDHT() {
  DHTPair pair;
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    pair.humidity = -1.0f;
    pair.temperature = -1.0f;
    return &pair;
  }

  pair.humidity = h;
  pair.temperature = t;

  return &pair;

  // Serial.print("DHT Sensor Values: Humidity: ");
  // Serial.print(h);
  // Serial.print("; Temperature (\xC2\xB0");
  // Serial.print("C): ");
  // Serial.println(t);
}

float calculateState(float prev_state, int soil_moisture,
DHTPair* dhtp) {
  float state = prev_state;
  float soil_moisture_delta = 0;
  if (soil_moisture < 300) {
    soil_moisture_delta = (float) map(soil_moisture, 0, 300, -1, 0);
  } else if (soil_moisture > 700) {
    soil_moisture_delta = (float) map(soil_moisture, 700, 950, 0, -1);
  } else if (soil_moisture < 500) {
    soil_moisture_delta = (float) map(soil_moisture, 300, 500, 0, 1);
  } else if (soil_moisture >= 500) {
    soil_moisture_delta = (float) map(soil_moisture, 700, 500, 0, 1);
  }

  float air_humidity_delta = 0;
  if (dhtp->humidity < 40.0f) {
    air_humidity_delta = (float) map((long) dhtp->humidity, 40, 0, 0, -1);
  } else if (dhtp->humidity > 70.0f) {
    air_humidity_delta = (float) map((long) dhtp->humidity, 70, 100, 0, -1);
  } else if (dhtp->humidity < 55.0f) {
    air_humidity_delta = (float) map((long) dhtp->humidity, 40, 55, 0, 1);
  } else if (dhtp->humidity >= 55.0f) {
    air_humidity_delta = (float) map((long) dhtp->humidity, 70, 55, 0, 1);
  }

  float air_temp_delta = 0;
  if (dhtp->temperature < 13.0f) {
    air_temp_delta = (float) map((long) dhtp->temperature, 13, 0, 0, -1);
  } else if (dhtp->temperature > 27.0f) {
    air_temp_delta = (float) map((long) dhtp->temperature, 27, 50, 0, -1);
  } else if (dhtp->temperature < 20.0f) {
    air_temp_delta = (float) map((long) dhtp->temperature, 13, 20, 0, 1);
  } else if (dhtp->temperature >= 20.0f) {
    air_temp_delta = (float) map((long) dhtp->temperature, 27, 20, 0, 1);
  }

  float delta = (MOISTURE_WEIGHT * soil_moisture_delta) + (HUMIDITY_WEIGHT * air_humidity_delta) + (TEMPERATURE_WEIGHT * air_temp_delta);

  delta = constrain(delta, -1.0f, 1.0f);

  state += delta;

  state = constrain(state, 0.0f, 100.0f);
  Serial.print("Current state: ");
  Serial.println(state);
}