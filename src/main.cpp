#include <Arduino.h>
#include <WiFi.h>
#include <esp_wifi.h>

struct packet{
  wifi_pkt_rx_ctrl_t rx_ctrl;
  unsigned version : 4;
  unsigned header_length : 4;
  uint8_t typeofservice;
  uint16_t total_length;
  uint16_t identifier;
  unsigned flags : 4;
  unsigned fragment_offset : 12;
  uint8_t time_to_live;
  uint8_t protocal;
  uint16_t header_checksum;
  uint8_t source_address[4];
  uint8_t destination_address[4];
  unsigned options : 24;
};


void formatIP(uint8_t IP[4]){
  for (int i = 0; i < 4; i++){
    Serial.print(IP[i]);
    if(i < 3){
    Serial.print(".");
    }
  }
}

void onPacketReceived(void *buffer, wifi_promiscuous_pkt_type_t type) {
  wifi_promiscuous_pkt_t *rawPacket = (wifi_promiscuous_pkt_t *)buffer;
  packet *parsedPacket = (struct packet *)buffer;
  int rssi = parsedPacket->rx_ctrl.rssi;
  if (type == WIFI_PKT_DATA){
    uint16_t etherType = ((uint16_t)rawPacket->payload[12] << 8) | (rawPacket->payload[13]);
    if(etherType==0x0800){
      Serial.print("RSSI: ");
      Serial.print(rssi);

      Serial.print(" Source IP: ");
      formatIP(parsedPacket->source_address);

      Serial.print(" Destination IP: ");
      formatIP(parsedPacket->destination_address);

    delay(1000);
    }
  }
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
