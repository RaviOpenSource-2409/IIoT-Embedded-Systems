#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

#define RELAYPIN 5
#define LEDPIN 15

// WiFi and ThingsBoard
const char* ssid = "project2";
const char* password = "realme11";
const char* mqtt_server = "demo.thingsboard.io";
const char* token = "clgRHclL53CEgJd5ge0R";

WiFiClient espClient;
PubSubClient client(espClient);

bool occupancy = false;
bool acStatus = false;
float temperature = 0.0;
bool manualOverride = false;
bool manualRelayState = false;

void setup_wifi() {
  Serial.print("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\n✅ WiFi connected!");
}

void rpcCallback(char* topic, byte* payload, unsigned int length) {
  payload[length] = '\0';
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, payload);
  if (error) return;

  String method = doc["method"];
  if (method == "setAC") {
    manualRelayState = doc["params"];
    manualOverride = true;
    digitalWrite(RELAYPIN, manualRelayState);
    acStatus = manualRelayState;
    digitalWrite(LEDPIN, acStatus ? HIGH : LOW);
    Serial.println(String("Manual AC: ") + (acStatus ? "ON" : "OFF"));
  } else if (method == "autoMode") {
    manualOverride = false;
    Serial.println("Switched to Auto Mode");
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    String clientId = "ESP32-" + String(random(0xffff), HEX);
    if (client.connect(clientId.c_str(), token, NULL)) {
      Serial.println("Connected to ThingsBoard!");
      client.subscribe("v1/devices/me/rpc/request/+");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(RELAYPIN, OUTPUT);
  pinMode(LEDPIN, OUTPUT);

  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(rpcCallback);

  randomSeed(analogRead(0));
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  // Dummy data
  occupancy = random(0, 2); // true or false

  // Simulated temperature with realistic fluctuations
  static float temp = 26.0;
  float fluctuation = random(-10, 11) / 10.0; // -1.0 to +1.0
  temp += fluctuation;
  if (temp < 24) temp = 24;
  if (temp > 33) temp = 33;
  temperature = temp;

  // Control logic
  if (!manualOverride) {
    if (occupancy && temperature > 27.0) {
      digitalWrite(RELAYPIN, HIGH);
      acStatus = true;
    } else {
      digitalWrite(RELAYPIN, LOW);
      acStatus = false;
    }
  }

  digitalWrite(LEDPIN, acStatus ? HIGH : LOW);  // LED shows AC status

  // Send telemetry
  String payload = "{";
  payload += "\"temperature\": " + String(temperature, 2) + ",";
  payload += "\"occupancy\": " + String(occupancy ? "true" : "false") + ",";
  payload += "\"ac_status\": " + String(acStatus ? "true" : "false") + ",";
  payload += "\"manual_override\": " + String(manualOverride ? "true" : "false");
  payload += "}";

  client.publish("v1/devices/me/telemetry", payload.c_str());
  Serial.println("📤 Sent: " + payload);

  delay(5000);
}
