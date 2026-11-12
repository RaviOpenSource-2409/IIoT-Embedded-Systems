# Bluetooth Serial Communication with ESP32

Two-way wireless communication between an ESP32 and a smartphone using Bluetooth Serial. The ESP32 sends a text message to the phone every 3 seconds and shows any message received from the phone on the Serial Monitor. No WiFi or internet is needed.

## Hardware

| Component | Quantity | Role |
|-----------|----------|------|
| ESP32 Dev Board | 1 | Acts as the Bluetooth device (`ESP32_BT`) |
| Smartphone | 1 | Connects over Bluetooth using a serial terminal app |

## Pin Configuration

No external wiring is required. The ESP32 uses its built-in Bluetooth.

## Libraries

No external library is required. `BluetoothSerial.h` comes with the ESP32 Arduino core.

## How It Works

1. The ESP32 starts the Serial Monitor at 115200 baud.
2. Bluetooth is started with the device name `ESP32_BT` using `SerialBT.begin()`.
3. Every 3 seconds the ESP32 sends "Hello from ESP32!" to the connected phone using `SerialBT.println()`.
4. When the phone sends a message, the ESP32 checks `SerialBT.available()`, reads it character by character and prints it on the Serial Monitor.

## How to Run

1. Upload `Bluetooth_Serial_Basic.ino` to the ESP32.
2. Open the Serial Monitor (115200 baud).
3. On your phone, turn on Bluetooth and pair with `ESP32_BT`.
4. Open a Bluetooth serial terminal app (for example, Serial Bluetooth Terminal) and connect to `ESP32_BT`.
5. The app will show "Hello from ESP32!" every 3 seconds.
6. Send any text from the app and it will appear on the Serial Monitor as "Received from App: ...".

## Sample Output

Serial Monitor:
```
Bluetooth Started! Now you can connect.
Received from App: Hello ESP32
```

Phone app:
```
Hello from ESP32!
Hello from ESP32!
```

## Concepts Learned

- Using Bluetooth Classic on ESP32 with `BluetoothSerial`
- Sending data from ESP32 to a phone wirelessly
- Receiving data from a phone and reading it on the ESP32
- Reading incoming serial data using `available()` and `read()`

## Notes

- This uses Bluetooth Classic, so it works on the original ESP32 but not on ESP32-S2, S3 or C3.
- Because of `delay(3000)` in the loop, incoming messages are checked once every 3 seconds, so they may show on the Serial Monitor with a small delay.
- The Bluetooth device name can be changed in `SerialBT.begin("ESP32_BT")`.

## Demo

Demo video: [LinkedIn post](https://lnkd.in/p/gRVWSw3R)
