struct DHTPair {
  float humidity;
  float temperature;
};

DHTPair* getDHT();
int calculateState(int prev_state, int soil_moisture, DHTPair* dhtp);

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

int calculateState(int prev_state, int soil_moisture,
DHTPair* dhtp) {
  int state = prev_state;
  if (soil_moisture < 300) {
    // Soil is dry.
  } else if (soil_moisture > 700) {
    // Soil is oversaturated
  } else {
    // Soil is humid
  }

  // Standard humidity preferences
  if (dhtp->humidity < 40.0f) {
    // Air is too arid
  } else if (dhtp->humidity > 70.0f) {
    // Air is too humid
  } else {
    // Air is just right
  }

  // Standard temp preferences
  if (dhtp->temperature < 13.0f) {
    // Air too cold
  } else if (dhtp->temperature > 27.0f) {
    // Air too hot
  } else {
    // Air just right
  }

  state = constrain(state, 0, 100);
  Serial.print("Current state: ");
  Serial.println(state);
}