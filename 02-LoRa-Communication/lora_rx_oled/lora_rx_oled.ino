#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <LoRa.h>

// Pin definitions for LoRa module
#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 23
#define DIO0 26
#define BAND 866E6

// OLED display pins and settings
#define OLED_SDA 21
#define OLED_SCL 22
#define OLED_RST -1   // OLED has no reset pin on this board
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// OLED display setup
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST);

void startOLED() {
  Wire.begin(OLED_SDA, OLED_SCL);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3c, false, false)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (1);
  }
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("LORA RX");
  display.display();
}

void startLoRa() {
  SPI.begin(SCK, MISO, MOSI, SS);
  LoRa.setPins(SS, RST, DIO0);

  while (!LoRa.begin(BAND)) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("LoRa Initialized");
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("LoRa Init OK!");
  display.display();
  delay(10);
}

void receiveReadings() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String receivedMessage = "";
    while (LoRa.available()) {
      receivedMessage += (char)LoRa.read();
    }

    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("Received:");
    display.setCursor(0, 10);
    display.print(receivedMessage);
    display.display();

    Serial.println("Received: " + receivedMessage);
  }
}

void setup() {
  Serial.begin(9600);
  startOLED();
  startLoRa();
}

void loop() {
  receiveReadings();
}
