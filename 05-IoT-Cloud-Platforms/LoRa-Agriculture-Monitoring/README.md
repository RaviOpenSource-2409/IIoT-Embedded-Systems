# LoRa Agriculture Monitoring with ThingsBoard

A LoRa based multi-sensor monitoring system for agriculture. A sensor node placed in the field reads temperature, humidity, soil moisture, pH, light intensity and rain status, and sends the data over LoRa every 10 seconds. A gateway ESP32 receives the data and forwards it to ThingsBoard over WiFi using MQTT. No WiFi is needed in the field.

## Hardware

| Component | Quantity | Role |
|---|---|---|
| ESP32 with LoRa module (SX1278, 433 MHz) | 2 | One sensor node, one gateway |
| DHT22 | 1 | Temperature and humidity |
| Soil moisture sensor | 1 | Soil moisture (analog) |
| pH sensor | 1 | pH value (analog) |
| Rain sensor | 1 | Rain detection (digital) |
| BH1750 | 1 | Light intensity in lux (I2C) |

## Pin Configuration

**Sensor Node**

| Signal | GPIO |
|---|---|
| DHT22 DATA | 13 |
| Soil moisture (analog) | 34 |
| pH sensor (analog) | 35 |
| Rain sensor (digital) | 12 |
| BH1750 | I2C (default SDA / SCL) |
| LoRa SS (NSS) | 18 |
| LoRa RST | 14 |
| LoRa DIO0 | 26 |

**Gateway**

| Signal | GPIO |
|---|---|
| LoRa SS (NSS) | 18 |
| LoRa RST | 14 |
| LoRa DIO0 | 26 |

Frequency: 433 MHz

## Libraries

- LoRa by Sandeep Mistry
- DHT sensor library by Adafruit
- Adafruit Unified Sensor
- BH1750 by Christopher Laws
- PubSubClient by Nick O'Leary

## How It Works

1. The sensor node reads all sensors every 10 seconds.
2. It packs the readings into a JSON style string, for example `{"temp":27.5,"humidity":60.0,"soil":2100,"ph":1800,"lux":350.0,"rain":1}`.
3. The string is sent over LoRa using `LoRa.beginPacket()`, `LoRa.print()` and `LoRa.endPacket()`.
4. The gateway checks for packets with `LoRa.parsePacket()` and reads the message.
5. The gateway publishes the same message to ThingsBoard on the topic `v1/devices/me/telemetry` over MQTT.
6. ThingsBoard stores each key as telemetry and shows it on the dashboard.

```
Sensors -> ESP32 Sensor Node -> LoRa (433 MHz) -> ESP32 Gateway -> WiFi / MQTT -> ThingsBoard
```

## Files

| File | Description |
|---|---|
| `lora_sensor_node/lora_sensor_node.ino` | Sensor node: reads sensors and sends data over LoRa |
| `lora_gateway/lora_gateway.ino` | Gateway: receives LoRa data and publishes it to ThingsBoard |

## How to Run

1. Install the libraries listed above.
2. Create a device in ThingsBoard and copy its access token.
3. In `lora_gateway.ino`, set `ssid`, `password` and `token`.
4. Upload `lora_sensor_node.ino` to the sensor node board.
5. Upload `lora_gateway.ino` to the gateway board.
6. Open the Serial Monitor (9600 baud) on both boards.
7. Check the device's Latest telemetry tab in ThingsBoard for `temp`, `humidity`, `soil`, `ph`, `lux` and `rain`.

## Concepts Learned

- Long-range wireless communication using LoRa
- Building a LoRa to MQTT gateway
- Interfacing multiple sensors with ESP32 (analog, digital and I2C)
- Sending sensor data to ThingsBoard using MQTT

## Notes

- Soil moisture and pH values are raw ADC readings (0 to 4095). They need calibration to get percentage or real pH.
- The rain sensor output depends on the module. Usually 0 means rain and 1 means dry.
- If a sensor read fails, the value can become `nan` and ThingsBoard will ignore that packet.
- WiFi credentials and the access token in the code are placeholders. Replace them with your own and never commit real ones.
- Both boards must use the same LoRa frequency. Change it to match your region if needed.

## Demo

Demo video: [LinkedIn post](PASTE_YOUR_LINKEDIN_POST_LINK_HERE)
