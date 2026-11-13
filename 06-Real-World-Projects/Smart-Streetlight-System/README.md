# Smart Street Light System

An IoT based smart street light system installed and tested in my college. An ESP32 reads ambient light from a light sensor and controls a relay to switch the street light automatically. The lights follow a time schedule and can also be controlled remotely from a ThingsBoard dashboard. This reduces energy wastage and removes the need for manual switching.

## Hardware

| Component | Quantity | Role |
|---|---|---|
| ESP32 | 1 | Main controller with WiFi |
| Light sensor (LDR) | 1 | Detects ambient light |
| Relay module | 1 | Switches the street light |
| Street light / lamp | 1 | Load controlled by the relay |

## Pin Configuration

| Signal | GPIO |
|---|---|
| Light sensor (analog) | 15 |
| Relay | 19 |

Check these against your wiring and change them if your setup differs.

## Libraries

- WiFi (built in with the ESP32 core)
- PubSubClient by Nick O'Leary

## How It Works

1. The ESP32 connects to WiFi and then to ThingsBoard over MQTT.
2. The light sensor measures the ambient light level.
3. **Automatic mode:** the light turns ON when it is dark and the time is after 5:30 PM, and turns OFF after 6:00 AM.
4. **Manual mode:** the light can be switched ON or OFF remotely from the ThingsBoard dashboard.
5. The relay status is sent to ThingsBoard as telemetry and shown on the dashboard.

```
Light Sensor -> ESP32 -> Relay -> Street Light
                  |
               MQTT
                  |
            ThingsBoard Dashboard (monitoring and remote ON/OFF)
```

## Features

- ESP32 based automation of the street light
- Light intensity based control using an LDR
- Time based operation: ON after 5:30 PM and OFF after 6:00 AM
- Remote ON/OFF control through ThingsBoard
- Live status on a ThingsBoard dashboard

## Files

| File | Description |
|---|---|
| `smart_streetlight.ino` | ESP32 code for sensing, relay control and ThingsBoard communication |
| `images/dashboard.png` | ThingsBoard dashboard screenshot |

## How to Run

1. Install the PubSubClient library.
2. Create a device in ThingsBoard and copy its access token.
3. In `smart_streetlight.ino`, set `ssid`, `password` and `access_token`.
4. Connect the light sensor and the relay as per the pin configuration.
5. Upload the code to the ESP32 and open the Serial Monitor (115200 baud).
6. Open the ThingsBoard dashboard to monitor the status and control the light.

## Concepts Learned

- Reading an analog light sensor with the ESP32
- Switching a load with a relay module
- Time based automation
- Sending data to ThingsBoard and controlling a device remotely over MQTT

## Notes

- WiFi credentials and the access token in the code are placeholders. Replace them with your own and never commit real ones.
- The light sensor threshold may need adjusting for your environment.
- Use a properly rated relay and follow electrical safety when switching mains loads.
- This system was installed and tested in a real college setting.

## Demo

Demo video: [LinkedIn post](https://lnkd.in/p/gDPqvYBK)
