# ESP-NOW Temperature & Humidity Monitoring

Wireless communication between two ESP32 boards using the ESP-NOW protocol. The transmitter reads temperature and humidity from a DHT11 sensor and sends it to the receiver, which prints the values on the Serial Monitor. No WiFi router or internet is needed.

## Hardware

| Component | Quantity | Role |
|---|---|---|
| ESP32 | 2 | One transmitter, one receiver |
| DHT11 sensor | 1 | Temperature and humidity (connected to GPIO 4) |

## Libraries

- `esp_now.h` and `WiFi.h` (included with the ESP32 Arduino core)
- DHT sensor library by Adafruit

## How It Works

1. The transmitter reads real-time temperature and humidity from the DHT11 sensor every 2 seconds.
2. The data is packed into a `SensorData` struct and sent using `esp_now_send()`.
3. The receiver gets the data in the `OnDataRecv()` callback and prints it on the Serial Monitor.
4. Communication is MAC address based: the transmitter sends data to the receiver's MAC address.

## How to Run

1. Upload `rx_serial.ino` to the receiver ESP32 and note its MAC address.
2. Put that MAC address in `receiverMAC[]` in `tx_dht11.ino`.
3. Connect the DHT11 data pin to GPIO 4 of the transmitter ESP32.
4. Upload `tx_dht11.ino` to the transmitter ESP32.
5. Open the Serial Monitor (115200 baud) on both boards.

## Concepts Learned

- Peer-to-peer wireless communication with ESP-NOW
- MAC addressing and peer registration
- Send and receive callbacks
- Reading a DHT11 sensor and sending data using structs

## Notes

- Encryption is disabled (`peerInfo.encrypt = false`).
- If the DHT11 read fails, the transmitter prints an error and skips sending.
- Written for ESP32 Arduino core v3.x.

## Demo

Demo video: [LinkedIn post](https://lnkd.in/p/gZHpQnNr)
