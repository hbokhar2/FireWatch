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
  uint32_t source_address;
  uint32_t destination_address;
  unsigned options : 24;
};

void formatIP(uint32_t IP){
  
}

void onPacketReceived(void *buffer, wifi_promiscuous_pkt_type_t type){
  struct snifferpacket *sniffedpacket = (struct snifferpacket*)buffer;
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
