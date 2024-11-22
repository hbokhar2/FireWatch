#include <Arduino.h>
#include <WiFi.h>
#include <esp_wifi.h>

struct packet{
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

struct filteredpacket{
  uint8_t source_address[4];
  uint8_t destination_address[4];
};

void formatIP(uint8_t IP[4]){
  for (int i = 0; i < 4; i++){
    Serial.print(IP[i]);
    if(i < 3){
    Serial.print(".");
    }
  }
}

void processPacket(const packet& original_packet){
  filteredpacket filtered;
  memcpy(filtered.source_address, original_packet.source_address, sizeof(filtered.source_address));
  memcpy(filtered.destination_address, original_packet.destination_address, sizeof(filtered.destination_address));
}

void onPacketReceived(void *buffer, wifi_promiscuous_pkt_type_t type) {
  struct packet *sniffedpacket = (struct packet*)buffer;

  if (sniffedpacket->protocal == 4) {
    filteredpacket filtered;
    processPacket(*sniffedpacket);

    uint8_t sourceIP[4];
    uint8_t destIP[4];

    memcpy(sourceIP, filtered.source_address, sizeof(sourceIP));
    memcpy(destIP, filtered.destination_address, sizeof(destIP));

    Serial.print("Source IP: ");
    formatIP(sourceIP);

    Serial.print(" Destination IP: ");
    formatIP(destIP);
    Serial.println();

    delay(1000);
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
