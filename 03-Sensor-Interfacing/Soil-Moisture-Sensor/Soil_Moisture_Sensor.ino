#define SOIL_MOISTURE_PIN 34  // Analog pin on ESP32

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Soil Moisture Sensor Reading Started...");
}

void loop() {
  int moistureValue = analogRead(SOIL_MOISTURE_PIN); // Read analog value
  float percentage = ((float)moistureValue / 4095.0) * 100;

  Serial.print("Raw Moisture Value: ");
  Serial.print(moistureValue);
  Serial.print(" | Percentage: ");
  Serial.print(percentage, 2); // 2 decimal places
  Serial.println(" %");

  delay(1000);
}
