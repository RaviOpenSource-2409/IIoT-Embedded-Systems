// esp now transmitter esp 32

#include <esp_now.h>
#include <WiFi.h>
#include "DHT.h"

#define DHTPIN 4      // Pin where the DHT11 is connected
#define DHTTYPE DHT11 // DHT 11 type

DHT dht(DHTPIN, DHTTYPE);

// Receiver MAC Address
uint8_t receiverMAC[] = {0x10, 0x06, 0x1C, 0xF6, 0x28, 0x00}; 

struct SensorData {
    float temperature;
    float humidity;
};

void OnDataSent(const uint8_t *mac, esp_now_send_status_t status) {
    Serial.print("Last Packet Send Status: ");
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup() {
    Serial.begin(115200);
    dht.begin();
    WiFi.mode(WIFI_STA); // Set device as Station

    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    esp_now_register_send_cb(OnDataSent); // Register callback
    esp_now_peer_info_t peerInfo = {};
    memcpy(peerInfo.peer_addr, receiverMAC, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;

    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println("Failed to add peer");
        return;
    }
}

void loop() {
    SensorData data;
    data.temperature = dht.readTemperature();
    data.humidity = dht.readHumidity();

    if (isnan(data.temperature) || isnan(data.humidity)) {
        Serial.println("Failed to read from DHT sensor!");
    } else {
        Serial.printf("Sending: Temperature = %.2f °C, Humidity = %.2f %%\n", data.temperature, data.humidity);
        esp_now_send(receiverMAC, (uint8_t *)&data, sizeof(data));
    }
    delay(2000); // Send data every 2 seconds
}
