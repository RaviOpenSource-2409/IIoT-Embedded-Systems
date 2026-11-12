# LoRa Communication with OLED Display

Wireless communication between two ESP32 boards with LoRa modules. The transmitter sends a text message over LoRa every 2 seconds. The receiver displays it on an SSD1306 OLED and the Serial Monitor. No WiFi or internet is needed.

## Hardware

| Component | Quantity | Role |
|---|---|---|
| ESP32 with LoRa module | 2 | One transmitter, one receiver |
| SSD1306 OLED (128x64, I2C) | 2 | Shows status and received message |

## Pin Configuration

| Signal | GPIO |
|---|---|
| LoRa SCK | 5 |
| LoRa MISO | 19 |
| LoRa MOSI | 27 |
| LoRa SS (CS) | 18 |
| LoRa RST | 23 |
| LoRa DIO0 | 26 |
| OLED SDA | 21 |
| OLED SCL | 22 |

Frequency: 866 MHz

## Libraries

- LoRa by Sandeep Mistry
- Adafruit SSD1306
- Adafruit GFX

## How It Works

1. Both boards initialize the OLED and the LoRa module.
2. The transmitter sends a text packet every 2 seconds using `LoRa.beginPacket()`, `LoRa.print()` and `LoRa.endPacket()`.
3. The transmitter also generates random demo temperature values, shown on its OLED and Serial Monitor.
4. The receiver checks for packets using `LoRa.parsePacket()`, reads the message and shows it on its OLED and Serial Monitor.

## How to Run

1. Install the libraries listed above.
2. Upload `lora_tx_oled.ino` to the transmitter board.
3. Upload `lora_rx_oled.ino` to the receiver board.
4. Open the Serial Monitor (9600 baud) on both boards.

## Concepts Learned

- Long-range wireless communication using LoRa
- SPI communication with the LoRa module
- Driving an SSD1306 OLED over I2C
- Sending and receiving LoRa packets

## Notes

- The transmitted message is a fixed text string. The temperature values are random demo data and are not sent over LoRa.
- Pin numbers match a board where the OLED has no reset pin (`OLED_RST = -1`). Change them if your board differs.
- Change `BAND` in the code to match your region's LoRa frequency.

## Demo

Demo video: [LinkedIn post](https://lnkd.in/p/gB8Fkk9t)
