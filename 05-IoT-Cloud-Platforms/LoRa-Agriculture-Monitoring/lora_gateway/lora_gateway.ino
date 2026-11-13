#include <WiFi.h>
#include <PubSubClient.h>
#include <SPI.h>
#include <LoRa.h>

// WiFi Credentials
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// ThingsBoard (MQTT) Settings
const char* mqttServer = "demo.thingsboard.io";
const int mqttPort = 1883;
const char* token = "YOUR_DEVICE_ACCESS_TOKEN";

// LoRa Pins
#define SS 18
#define RST 14
#define DIO0 26

WiFiClient wifiClient;
PubSubClient client(wifiClient);

void connectWiFi() {
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }
  Serial.println("\nWiFi Connected");
}

void connectMQTT() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    if (client.connect("ESP32_Gateway", token, "")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  connectWiFi();

  client.setServer(mqttServer, mqttPort);
  connectMQTT();

  LoRa.setPins(SS, RST, DIO0);
  if (!LoRa.begin(433E6)) {
    Serial.println("LoRa init failed");
    while (1);
  }
  Serial.println("LoRa Gateway Ready");
}

void loop() {
  if (!client.connected()) {
    connectMQTT();
  }
  client.loop();

  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String incoming = "";
    while (LoRa.available()) {
      incoming += (char)LoRa.read();
    }
    Serial.println("Received: " + incoming);

    // Send to ThingsBoard
    client.publish("v1/devices/me/telemetry", incoming.c_str());
    Serial.println("Sent to ThingsBoard");
  }
}
