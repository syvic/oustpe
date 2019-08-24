#include <WiFi.h>
#include <esp_now.h>
#include <stdint.h>
#include <string.h>

#include "oustpe.h"

#define WIFI_CHANNEL    1
#define LED_PIN         18
#define PULSADOR        15

uint32_t uuid;

void setup() {
  Serial.begin(115200);
  Serial.println("Arrancando");

  pinMode(LED_PIN, OUTPUT);

  espnow_network_setup();
  uuid = utils_get_chip_id();
}

void loop() {
  uint16_t group=0x5A5A;
  
  yield();

  utils_test_sender(group);


}
