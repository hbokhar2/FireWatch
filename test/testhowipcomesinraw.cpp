#include <Arduino.h>
#include <esp_wifi.h>
#include <WiFi.h>

void onPacketReceived(void *buffer, wifi_promiscuous_pkt_type_t type) {
    uint8_t *rawPacket = (uint8_t*)buffer;
    int packetLength = 160; // Replace this with the actual packet length

    for (int i = 0; i < packetLength; i++) {
        // Print each byte as a hexadecimal value
        Serial.print(rawPacket[i]);
        Serial.print(' '); // Add a space for better readability
    }

    Serial.println(); // Move to the next line after printing the packet
}

void setup(){   
    Serial.begin(115200);
    delay(10);

    WiFi.mode(WIFI_STA);
    esp_wifi_set_promiscuous(true);
    esp_wifi_set_promiscuous_rx_cb(onPacketReceived);
}

void loop(){
    
}