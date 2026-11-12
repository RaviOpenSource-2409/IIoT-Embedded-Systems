#include <WiFi.h>

String macAddress;

void setup() {
  Serial.begin(115200);
  Serial.println("Scanning for ESP32 MAC Address...");

  // Print the MAC address of the ESP32
   macAddress = WiFi.macAddress();
  Serial.print("ESP32 MAC Address: ");
  Serial.println(macAddress);
}

void loop() {
  // Nothing to do here
   Serial.print("ESP32 MAC Address: ");
  Serial.println(macAddress);
  delay(3000);
}
