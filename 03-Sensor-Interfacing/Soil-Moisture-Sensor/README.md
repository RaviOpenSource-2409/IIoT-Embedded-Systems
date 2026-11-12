# Soil Moisture Sensor with ESP32

Reads soil moisture using an analog soil moisture sensor and prints the
raw ADC value and moisture percentage on the Serial Monitor.

## Hardware
- ESP32 Dev Board
- Soil Moisture Sensor (analog output)
- Jumper wires

## Wiring
| Sensor Pin | ESP32 Pin |
|------------|-----------|
| VCC        | 3.3V      |
| GND        | GND       |
| AO / SIG   | GPIO 34   |

## How it works
- GPIO 34 (ADC1) reads the sensor's analog output (12-bit, 0-4095).
- The raw value is mapped to a moisture percentage and printed every 1 second.
- Dry soil gives a higher raw value and wet soil gives a lower one, so
  calibrate `DRY_VALUE` and `WET_VALUE` in the code for your sensor.

## Serial Monitor
Baud rate: `115200`

## Sample Output
```
Raw Moisture Value: 2450 | Moisture: 42 %
```
