#include "BluetoothSerial.h"

BluetoothSerial SerialBT;  // Bluetooth Serial Object Create

void setup() {
  Serial.begin(115200);   // Serial Monitor ke liye baud rate set
  SerialBT.begin("ESP32_BT");  // Bluetooth ka naam set karein
  Serial.println("Bluetooth Started! Now you can connect.");
}

void loop() {
  // *ESP32 se Bluetooth App pe Message Send*
  SerialBT.println("Hello from ESP32!");  // Sirf App pe message jayega
  delay(3000);  // Har 3 sec me message send karega

  // *Bluetooth Serial App se ESP32 pe Message Receive (Sirf Serial Monitor pe Show Hoga)*
  if (SerialBT.available()) {
    String receivedData = "";
    while (SerialBT.available()) {
      char c = SerialBT.read();
      receivedData += c;
    }

    Serial.print("Received from App: ");
    Serial.println(receivedData);  // Sirf Serial Monitor pe show karega (App pe wapas nahi jayega)
  }
}
