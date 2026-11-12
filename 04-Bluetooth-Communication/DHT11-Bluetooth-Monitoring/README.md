# DHT11 Temperature and Humidity Monitoring over Bluetooth with ESP32

Reads temperature and humidity from a DHT11 sensor connected to an ESP32 and sends the values to a smartphone over Bluetooth Serial every 2 seconds. The same data is also shown on the Serial Monitor. No WiFi or internet is needed.

## Hardware

| Component | Quantity | Role |
|-----------|----------|------|
| ESP32 Dev Board | 1 | Reads the sensor and acts as the Bluetooth device (`NAZ_DHT`) |
| DHT11 Sensor | 1 | Measures temperature and humidity |
| Smartphone | 1 | Receives the data using a Bluetooth serial terminal app |
| Jumper wires | 3 | Connections |

## Pin Configuration

| DHT11 Pin | ESP32 Pin |
|-----------|-----------|
| VCC | 3.3V |
| GND | GND |
| DATA | GPIO 14 |

## Libraries

- DHT sensor library by Adafruit
- Adafruit Unified Sensor
- BluetoothSerial (comes with the ESP32 Arduino core)

## How It Works

1. The ESP32 starts the Serial Monitor at 115200 baud.
2. Bluetooth is started with the device name `NAZ_DHT` and the DHT11 sensor is initialized.
3. Every 2 seconds the ESP32 reads temperature and humidity using `dht.readTemperature()` and `dht.readHumidity()`.
4. If the reading fails (`isnan`), an error message is sent to both the Serial Monitor and the phone.
5. If the reading is successful, the values are combined into one text string and sent to the Serial Monitor and the phone over Bluetooth.

## How to Run

1. Install the libraries listed above.
2. Connect the DHT11 to the ESP32 as shown in the pin configuration.
3. Upload `DHT11_Bluetooth_Monitoring.ino` to the ESP32.
4. Open the Serial Monitor (115200 baud).
5. On your phone, pair with `NAZ_DHT` in the Bluetooth settings.
6. Open a Bluetooth serial terminal app (for example, Serial Bluetooth Terminal) and connect to `NAZ_DHT`.
7. The temperature and humidity values will appear in the app every 2 seconds.

## Sample Output

```
Temperature: 28.00°C, Humidity: 65.00%
Temperature: 28.00°C, Humidity: 64.00%
```

## Concepts Learned

- Interfacing a DHT11 sensor with ESP32
- Sending sensor data wirelessly using Bluetooth Classic
- Handling failed sensor readings using `isnan()`
- Formatting sensor data as text for display on a phone

## Notes

- This uses Bluetooth Classic, so it works on the original ESP32 but not on ESP32-S2, S3 or C3.
- DHT11 gives whole number readings with limited accuracy (about ±2°C and ±5% humidity).
- The DHT11 needs about 2 seconds between readings, so keep the delay at 2000 ms or more.
- The Bluetooth device name can be changed in `SerialBT.begin("NAZ_DHT")`.

## Demo

Demo video: [LinkedIn post](https://lnkd.in/p/gRVWSw3R)
