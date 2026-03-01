#ifndef SOIL_HYDROMETER_H
#define SOIL_HYDROMETER_H

#include <Arduino.h>
#include "Adafruit_Sensor.h"
#include "DHT.h"

// =====================
// Structs
// =====================

struct DHTPair {
    float humidity;
    float temperature;
};

// =====================
// Constants
// =====================

#define MOISTURE_WEIGHT    0.5
#define TEMPERATURE_WEIGHT 0.3
#define HUMIDITY_WEIGHT    0.2

#define HYDROMETER 0
#define DHTPIN     2
#define DHTTYPE    DHT11

// =====================
// Function Prototypes
// =====================

void setupSoil();
int getMoi();
DHTPair* getDHT();
float calculateState(float prev_state, int soil_moisture, DHTPair* dhtp);

#endif