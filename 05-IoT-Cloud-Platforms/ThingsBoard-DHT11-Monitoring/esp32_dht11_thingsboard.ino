#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

// ---------- Config (replace before uploading) ----------
const char* WIFI_SSID     = "YOUR_WIFI_NAME";
const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";

const char* MQTT_SERVER   = "demo.thingsboard.io";   // or thingsboard.cloud
const int   MQTT_PORT     = 1883;
const char* ACCESS_TOKEN  = "YOUR_DEVICE_ACCESS_TOKEN";

#define DHTPIN  4
#define DHTTYPE DHT11

const unsigned long SEND_INTERVAL = 5000;  // ms
// -------------------------------------------------------

DHT dht(DHTPIN, DHTTYPE);
WiFiClient espClient;
PubSubClient client(espClient);

unsigned long lastSend = 0;

void connectWiFi() {
  Serial.print("Connecting to WiFi");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected, IP: " + WiFi.localIP().toString());
}

void connectMQTT() {
  while (!client.connected()) {
    Serial.print("Connecting to ThingsBoard...");
    // ThingsBoard: username = access token, password empty
    if (client.connect("ESP32_DHT11_Client", ACCESS_TOKEN, NULL)) {
      Serial.println("connected");
    } else {
      Serial.printf("failed, rc=%d. Retry in 3s\n", client.state());
      delay(3000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  connectWiFi();
  client.setServer(MQTT_SERVER, MQTT_PORT);
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) connectWiFi();
  if (!client.connected()) connectMQTT();
  client.loop();

  if (millis() - lastSend >= SEND_INTERVAL) {
    lastSend = millis();

    float temperature = dht.readTemperature();  // Celsius
    float humidity    = dht.readHumidity();

    if (isnan(temperature) || isnan(humidity)) {
      Serial.println("Failed to read from DHT11 sensor!");
      return;
    }

    String payload = "{\"temperature\":" + String(temperature, 1) +
                     ",\"humidity\":" + String(humidity, 1) + "}";

    if (client.publish("v1/devices/me/telemetry", payload.c_str())) {
      Serial.println("Sent: " + payload);
    } else {
      Serial.println("Publish failed");
    }
  }
}
