#include "BluetoothSerial.h" // Include Bluetooth Serial library
#include "DHT.h"             // Include DHT sensor library

#define DHTPIN 14            // Define the DHT sensor pin
#define DHTTYPE DHT11        // Define the DHT sensor type

BluetoothSerial SerialBT;    // Create a Bluetooth Serial object
DHT dht(DHTPIN, DHTTYPE);    // Initialize the DHT sensor

void setup() {
    Serial.begin(115200);    // Initialize Serial Monitor
    SerialBT.begin("NAZ_DHT"); // Set Bluetooth device name
    Serial.println("Bluetooth Device is Ready to Pair");

    dht.begin(); // Initialize DHT sensor
}

void loop() {
    float temperature = dht.readTemperature(); // Read temperature
    float humidity = dht.readHumidity();      // Read humidity

    // Check if reading is successful
    if (isnan(temperature) || isnan(humidity)) {
        Serial.println("Failed to read from DHT sensor!");
        SerialBT.println("Failed to read from DHT sensor!");
    } else {
        // Send data via Bluetooth
        String data = "Temperature: " + String(temperature) + "°C, Humidity: " + String(humidity) + "%";
        Serial.println(data);  // Print to Serial Monitor
        SerialBT.println(data); // Send data over Bluetooth
    }

    delay(2000); // Wait 2 seconds before next reading
}
