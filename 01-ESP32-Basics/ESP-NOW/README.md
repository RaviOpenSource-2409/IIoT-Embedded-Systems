# ESP-NOW Temperature & Humidity Monitoring

Wireless communication between two ESP32 boards using the ESP-NOW protocol. The transmitter sends temperature and humidity data to the receiver, which prints the values on the Serial Monitor. No WiFi router or internet is needed.

## Hardware

| Component | Quantity | Role |
|---|---|---|
| ESP32 | 2 | One transmitter, one receiver |
| DHT11 sensor | 1 | Temperature and humidity (connected to GPIO 14) |

## Libraries

- `esp_now.h` and `WiFi.h` (included with the ESP32 Arduino core)
- DHT sensor library by Adafruit

## How It Works

1. The transmitter sends a `SensorData` struct every 2 seconds using `esp_now_send()`.
2. The receiver gets the data in the `OnDataRecv()` callback and prints it.
3. Communication is MAC address based: the transmitter sends data to the receiver's MAC address.

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

- The DHT11 reading lines in `tx_dht11.ino` are commented out. Fixed test values (23 °C, 45 %) are transmitted to verify ESP-NOW communication.
- Encryption is disabled (`peerInfo.encrypt = false`).
- Written for ESP32 Arduino core v3.x.

## Demo

Demo video: [LinkedIn post](https://lnkd.in/p/gZHpQnNr)
