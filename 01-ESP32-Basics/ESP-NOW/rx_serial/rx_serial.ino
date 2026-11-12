#include <esp_now.h>
#include <WiFi.h>

struct SensorData {
    float temperature;
    float humidity;
};

void OnDataRecv(const esp_now_recv_info *info, const uint8_t *data, int len) {
    SensorData receivedData;
    memcpy(&receivedData, data, sizeof(receivedData));
    Serial.printf("Received: Temperature = %.2f °C, Humidity = %.2f %%\n", receivedData.temperature, receivedData.humidity);
}

void setup() {
    Serial.begin(115200);
    WiFi.mode(WIFI_STA); // Set device as Station

    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }

    esp_now_register_recv_cb(OnDataRecv); // Register callback for received data
}

void loop() {
    // Nothing to do here, receiving happens in the callback
}

