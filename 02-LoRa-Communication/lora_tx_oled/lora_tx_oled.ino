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

// Array to store temperature data
float tempData[10] = {0};
int tempIndex = 0;

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
  display.print("LORA TX");
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

void sendReadings() {
  // Generate fake temperature data for demonstration
  float temperature = random(20, 35) + random(0, 100) / 100.0;
  tempData[tempIndex] = temperature;
  tempIndex = (tempIndex + 1) % 10;

  // Full history goes to Serial only
  String LoRaMessage = "TempData: ";
  for (int i = 0; i < 10; i++) {
    LoRaMessage += String(tempData[i], 2);
    if (i < 9) LoRaMessage += ", ";
  }

  LoRa.beginPacket();
  LoRa.print("Ravi Gupta");
  LoRa.endPacket();

  // OLED shows only the latest value so it fits on screen
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("LoRa Sent:");
  display.setCursor(0, 10);
  display.print("Ravi Gupta");
  display.setCursor(0, 20);
  display.print("Temp: ");
  display.print(temperature, 2);
  display.display();

  Serial.println("Sent: " + LoRaMessage);
}

void setup() {
  Serial.begin(9600);
  startOLED();
  startLoRa();
}

void loop() {
  sendReadings();
  delay(2000);
}
