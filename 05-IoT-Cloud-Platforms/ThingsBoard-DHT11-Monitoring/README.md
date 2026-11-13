# Real-time Temperature & Humidity Monitoring with ThingsBoard

Real-time IoT monitoring using an ESP32 and a DHT11 sensor. The ESP32 reads temperature and humidity every 5 seconds and sends the data to ThingsBoard over MQTT. A custom rule chain with a Script node validates the data and saves it as telemetry, and a dashboard shows live graphs.

## Hardware

| Component | Quantity | Role |
|---|---|---|
| ESP32 DevKit | 1 | Reads the sensor and publishes data over WiFi |
| DHT11 sensor | 1 | Measures temperature and humidity |

## Pin Configuration

| DHT11 Pin | ESP32 |
|---|---|
| VCC | 3.3V |
| GND | GND |
| DATA | GPIO 4 |

MQTT topic: `v1/devices/me/telemetry`

## Libraries

- PubSubClient by Nick O'Leary
- DHT sensor library by Adafruit
- Adafruit Unified Sensor

## How It Works

1. The ESP32 connects to WiFi and then to ThingsBoard over MQTT using the device access token.
2. Every 5 seconds it reads temperature and humidity from the DHT11 and publishes them as JSON, for example `{"temperature": 27.5, "humidity": 60.0}`.
3. In ThingsBoard, the rule chain **Temperature & Humidity Sensors** receives the message. A Script node validates the values and sets `sw` and `info` (HOT above 26 °C, otherwise normal).
4. The data is saved as telemetry and shown as live temperature and humidity graphs on the dashboard.

```
DHT11 -> ESP32 -> MQTT -> ThingsBoard -> Rule Chain (Script node) -> Dashboard
```

## Files

| File | Description |
|---|---|
| `esp32_dht11_thingsboard.ino` | ESP32 firmware (WiFi, DHT11, MQTT) |
| `temperature_script.js` | Script node code used in the rule chain |

## How to Run

1. Create a device in ThingsBoard and copy its access token.
2. Install the libraries listed above.
3. In `esp32_dht11_thingsboard.ino`, set `WIFI_SSID`, `WIFI_PASSWORD`, `MQTT_SERVER` and `ACCESS_TOKEN`.
4. Upload the sketch to the ESP32 and open the Serial Monitor (115200 baud).
5. In the ThingsBoard rule chain, add a Script Transformation node and paste `temperature_script.js`.
6. Create a dashboard with time-series charts for `temperature` and `humidity`.

## Concepts Learned

- Publishing sensor data over MQTT
- Connecting an ESP32 to an IoT cloud platform
- Building a ThingsBoard rule chain with a Script node
- Creating a real-time dashboard with live graphs

## Notes

- WiFi credentials and the access token in the code are placeholders. Replace them with your own and never commit real ones.
- The script only sets the `sw` flag and the `info` text. It does not switch a relay by itself.
- The DHT11 is accurate to about ±2 °C and ±5 % RH, and its valid range is 0-50 °C and 20-90 % RH.
- The key names in the payload (`temperature`, `humidity`) must match the keys used in the script and the dashboard.

## Demo

Demo video: [LinkedIn post](https://lnkd.in/p/eF7xb2iX)
