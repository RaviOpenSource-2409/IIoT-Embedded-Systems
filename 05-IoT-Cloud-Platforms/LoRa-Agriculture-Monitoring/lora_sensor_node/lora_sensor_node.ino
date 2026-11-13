#include <SPI.h>
#include <LoRa.h>
#include <DHT.h>
#include <Wire.h>
#include <BH1750.h>

// Sensor Pins
#define DHTPIN 13
#define DHTTYPE DHT22
#define SOIL_PIN 34
#define PH_PIN 35
#define RAIN_SENSOR_PIN 12

// Sensor Objects
DHT dht(DHTPIN, DHTTYPE);
BH1750 lightMeter;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  dht.begin();
  lightMeter.begin();

  pinMode(RAIN_SENSOR_PIN, INPUT);

  // LoRa Setup
  Serial.println("LoRa Sender Init...");
  LoRa.setPins(18, 14, 26); // NSS, RST, DIO0 for SX1278

  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa init failed. Check connections.");
    while (1);
  }

  Serial.println("LoRa Sender Ready.");
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int soilMoisture = analogRead(SOIL_PIN);
  int rainStatus = digitalRead(RAIN_SENSOR_PIN);
  int phValue = analogRead(PH_PIN);  // Needs calibration
  float lux = lightMeter.readLightLevel();

  // Format data in JSON-like string
  String data = "{";
  data += "\"temp\":" + String(temperature, 1) + ",";
  data += "\"humidity\":" + String(humidity, 1) + ",";
  data += "\"soil\":" + String(soilMoisture) + ",";
  data += "\"ph\":" + String(phValue) + ",";
  data += "\"lux\":" + String(lux, 1) + ",";
  data += "\"rain\":" + String(rainStatus);
  data += "}";

  Serial.println("Sending Data:");
  Serial.println(data);

  LoRa.beginPacket();
  LoRa.print(data);
  LoRa.endPacket();

  delay(10000); // Send every 10 seconds
}
