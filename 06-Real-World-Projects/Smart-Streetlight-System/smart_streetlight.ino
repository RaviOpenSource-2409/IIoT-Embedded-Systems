#include <PubSubClient.h>

#include <WiFi.h>
#include <PubSubClient.h>
 
#define PIR_PIN 4     // PIR sensor pin
#define LIGHT_SENSOR_PIN 15  // Light intensity sensor pin
#define RELAY_PIN 19        // Relay pin
 
// WiFi credentials
const char* ssid = "OnePlus";
const char* password = "99999999";
 
// ThingsBoard MQTT settings
const char* mqtt_server = "demo.thingsboard.io";  // Replace with your ThingsBoard server
const int mqtt_port = 1883;
const char* access_token = "KoVCbsKZB6vbNBh38PoL";   // Replace with your ThingsBoard access token
 
WiFiClient espClient;
PubSubClient client(espClient);
 
void setup() {
  Serial.begin(115200);
  // Setup pins
  pinMode(PIR_PIN, INPUT);
  pinMode(LIGHT_SENSOR_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);
  // Initial relay state
  digitalWrite(RELAY_PIN, LOW);
 
  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Connect to MQTT server
  client.setServer(mqtt_server, mqtt_port);
  connectToMQTT();
}
 
void connectToMQTT() {
  while (!client.connected()) {
    Serial.println("Connecting to ThingsBoard...");
    if (client.connect("ESP32Client", access_token, NULL)) {
      Serial.println("Connected to ThingsBoard");
    } 
    else {
      Serial.print("Failed to connect, rc=");
      Serial.print(client.state());
      delay(2000);
    }
  }
}
 
void sendRelayStatus(bool status) {
  // Prepare JSON payload
  String payload = "{\"relay_status\":\"";
  payload += status;
  payload += "\"}";
  // Publish to ThingsBoard
  if (client.publish("v1/devices/me/telemetry", payload.c_str())) {
    Serial.print("Status sent: ");
    Serial.println(status);
  } else {
    Serial.println("Failed to send relay status");
  }
}
 
void loop() {
  // Ensure MQTT connection
  if (!client.connected()) {
    connectToMQTT();
  }
  client.loop();
 
  // Read sensor values
  int pirState = digitalRead(PIR_PIN);
  int lightIntensity = analogRead(LIGHT_SENSOR_PIN);
 
  // Check conditions for turning relay on or off
  if (lightIntensity == 0 && pirState == HIGH) {
    digitalWrite(RELAY_PIN, HIGH);  // Turn relay ON
    sendRelayStatus(true);
    Serial.println("Motion detected, light intensity is zero: Relay ON");
  } else {
    digitalWrite(RELAY_PIN, LOW);   // Turn relay OFF
    sendRelayStatus(false);
    Serial.println("No motion or light intensity not zero: Relay OFF");
  }
 
  delay(1000);  // Adjust the delay as per your requirement
}
