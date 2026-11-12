# ESP-NOW Temperature & Humidity Monitoring

Wireless communication between two ESP32 boards using the ESP-NOW protocol. The transmitter reads temperature and humidity from a DHT11 sensor and sends it to the receiver, which prints the values on the Serial Monitor. No WiFi router or internet is needed.

## Hardware

| Component | Quantity | Role |
|---|---|---|
| ESP32 | 2 | One transmitter, one receiver |
| DHT11 sensor | 1 | Temperature and humidity (connected to GPIO 14) |

## Libraries

- `esp_now.h` and `WiFi.h` (included with the ESP32 Arduino core)
- DHT sensor library by Adafruit

## How It Works

1. The transmitter reads temperature and humidity every 2 seconds.
2. Data is packed into a `SensorData` struct and sent using `esp_now_send()`.
3. The receiver gets the data in the `OnDataRecv()` callback and prints it.

## How to Run

1. Upload `rx_serial.ino` to the receiver ESP32 and note its MAC address.
2. Put that MAC address in `receiverMAC[]` in `tx_dht11.ino`.
3. Upload `tx_dht11.ino` to the transmitter ESP32.
4. Open the Serial Monitor (115200 baud) on both boards.

## Concepts Learned

- Peer-to-peer wireless communication with ESP-NOW
- MAC addressing and peer registration
- Send and receive callbacks
- Sending sensor data using structs

## Notes

- In `tx_dht11.ino`, the DHT11 reading lines are commented out and test values (23 °C, 45 %) are used.
- Written for ESP32 Arduino core v3.x.
