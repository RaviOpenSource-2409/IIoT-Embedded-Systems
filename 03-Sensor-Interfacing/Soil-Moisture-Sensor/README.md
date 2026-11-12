# Soil Moisture Sensor with ESP32

Measures soil moisture using an analog soil moisture sensor connected to an ESP32. The ESP32 reads the sensor's analog output, converts it to a moisture percentage and prints both the raw value and the percentage on the Serial Monitor every second. No WiFi or internet is needed.

## Hardware

| Component | Quantity | Role |
|-----------|----------|------|
| ESP32 Dev Board | 1 | Reads the sensor and prints the output |
| Soil Moisture Sensor (analog) | 1 | Gives an analog value based on soil moisture |
| Jumper wires | 3 | Connections |

## Pin Configuration

| Sensor Pin | ESP32 Pin |
|------------|-----------|
| VCC | 3.3V |
| GND | GND |
| AO / SIG | GPIO 34 |

## Libraries

No external library is required. Only the default Arduino core for ESP32 is used.

## How It Works

1. The ESP32 starts the Serial Monitor at 115200 baud.
2. GPIO 34 (ADC1) reads the sensor output using `analogRead()`. The ESP32 ADC is 12-bit, so the raw value ranges from 0 to 4095.
3. The raw value is converted to a moisture percentage using `map()` and `constrain()`.
4. The raw value and the percentage are printed on the Serial Monitor every 1 second.

## How to Run

1. Connect the sensor to the ESP32 as shown in the pin configuration.
2. Upload `Soil_Moisture_Sensor.ino` to the ESP32.
3. Open the Serial Monitor (115200 baud).
4. Put the sensor in dry soil or air, then in water, and note the raw values.
5. Update `DRY_VALUE` and `WET_VALUE` in the code with your readings.

## Sample Output

```
Raw Moisture Value: 2450 | Moisture: 42 %
```

## Concepts Learned

- Reading analog sensors using the ESP32 ADC
- Converting raw ADC values into meaningful percentages
- Sensor calibration using `map()` and `constrain()`
- Serial Monitor debugging

## Notes

- Dry soil gives a higher raw value and wet soil gives a lower one, so calibration is needed for accurate percentage.
- `DRY_VALUE` and `WET_VALUE` differ from sensor to sensor. Change them to match your sensor.
- GPIO 34 is an ADC1 pin, so it keeps working even when WiFi is on.

## Demo

Demo video: [LinkedIn post](https://lnkd.in/p/gTx8p6Bs)
