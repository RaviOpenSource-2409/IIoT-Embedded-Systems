# Smart Energy Optimization System

An IoT based energy optimization system that switches an AC (relay) automatically based on room occupancy and temperature, and lets the user override it remotely from a ThingsBoard dashboard. The AC runs only when someone is present and the room is hot, which reduces wasted energy. An LED shows the current AC status.

## Hardware

| Component | Quantity | Role |
|---|---|---|
| ESP32 | 1 | Main controller with WiFi |
| Relay module | 1 | Switches the AC / load |
| LED | 1 | Shows AC ON/OFF status |

## Pin Configuration

| Signal | GPIO |
|---|---|
| Relay | 5 |
| Status LED | 15 |

## Libraries

- WiFi (built in with the ESP32 core)
- PubSubClient by Nick O'Leary
- ArduinoJson by Benoit Blanchon

## How It Works

1. The ESP32 connects to WiFi and then to ThingsBoard over MQTT.
2. Every 5 seconds it gets the room temperature and occupancy.
3. **Auto mode:** the relay (AC) turns ON only when the room is occupied and the temperature is above 27 °C. Otherwise it turns OFF.
4. **Manual mode:** the dashboard can send an RPC command to override the AC.
   - `setAC` with `true` or `false` turns the AC ON or OFF manually
   - `autoMode` returns the system to automatic control
5. The LED follows the AC status.
6. The ESP32 publishes the data to ThingsBoard as telemetry.

```
Temperature + Occupancy -> ESP32 -> Relay -> AC
                             |
                           MQTT
                             |
                ThingsBoard Dashboard (monitoring + manual override)
```

## Telemetry Sent

| Key | Description |
|---|---|
| `temperature` | Room temperature in °C |
| `occupancy` | `true` if the room is occupied |
| `ac_status` | `true` if the AC relay is ON |
| `manual_override` | `true` if manual mode is active |

Example: `{"temperature": 28.40, "occupancy": true, "ac_status": true, "manual_override": false}`

## RPC Commands

| Method | Params | Effect |
|---|---|---|
| `setAC` | `true` / `false` | Turns the AC ON or OFF and enables manual override |
| `autoMode` | none | Disables manual override and returns to auto control |

## Files

| File | Description |
|---|---|
| `smart_energy_optimization.ino` | ESP32 code for control logic, MQTT telemetry and RPC |

## How to Run

1. Install the PubSubClient and ArduinoJson libraries.
2. Create a device in ThingsBoard and copy its access token.
3. In `smart_energy_optimization.ino`, set `ssid`, `password` and `token`.
4. Connect the relay to GPIO 5 and the LED to GPIO 15.
5. Upload the code to the ESP32 and open the Serial Monitor (115200 baud).
6. In ThingsBoard, add switch or button widgets on the dashboard that send the `setAC` and `autoMode` RPC commands.

## Concepts Learned

- Rule based energy saving using occupancy and temperature
- Controlling a relay with ESP32
- Remote control using ThingsBoard RPC over MQTT
- Parsing JSON commands with ArduinoJson

## Notes

- In this code, temperature and occupancy are **simulated** (temperature varies between 24 and 33 °C and occupancy is random). Replace them with real sensor readings such as a PIR sensor and a temperature sensor for a real deployment.
- WiFi credentials and the access token in the code are placeholders. Replace them with your own and never commit real ones.
- Use a properly rated relay and follow electrical safety when switching an AC or any mains load.

## Demo

Demo video: [LinkedIn post](https://lnkd.in/p/g6yhrnNt)
