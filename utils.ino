#include "oustpe.h"

unsigned long utils_get_chip_id() {
  uint64_t chipid;
  unsigned long chipid_reduced;

  chipid = ESP.getEfuseMac();

  //De la MAC total del dispositivo                    (ej. 3C:71:BF:8A:DD:D8 <MAC>)
  //Nos quedamos con los 4 bytes menos significativos: (ej. D8:DD:8A:BF) <- En este orden

  chipid_reduced = ((chipid & 0xFFFF00000000) >> 16) | ((chipid & 0xFFFF0000) >> 16);

  return chipid_reduced;
}


void utils_test_sender(uint16_t group) {

  esp_now_msg_t msg;

  if (digitalRead(PULSADOR) == HIGH) {   // Mandar mensaje de JOIN
    msg.type = MSG_TYPE_JOIN;
    msg.uuid = my_uuid;
    msg.group = group;
    espnow_send_msg(&msg);
  }

  delay(1000);

  if (1) { // Mandar mensaje de muerte
    msg.type = MSG_TYPE_DEAD;
    msg.uuid = my_uuid;
    msg.group = group;
    espnow_send_msg(&msg);
  }

  delay(1000);
  
  if (1) { // Mandar mensaje de start
    msg.type = MSG_TYPE_START;
    msg.uuid = my_uuid;
    msg.group = group;
    espnow_send_msg(&msg);
  }

  delay(1000);

}
