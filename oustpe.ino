#include <WiFi.h>
#include <esp_now.h>
#include <stdint.h>
#include <string.h>

#include "oustpe.h"
#include "button.h"

#define WIFI_CHANNEL    1
#define LED_PIN         18
#define PULSADOR        15


#define MAX_PLAYERS     64
#define THRESHOLD       512

uint32_t my_uuid;
boolean recvd_msg_flag;
esp_now_msg_t recvd_msg;

uint32_t players[MAX_PLAYERS];
static byte num_players=1;

void setup() {
  Serial.begin(115200);
  Serial.println("Arrancando");

  pinMode(LED_PIN, OUTPUT);

  accel_config();

  espnow_network_setup();
  my_uuid = utils_get_chip_id();
}


void loop() {
  uint16_t group=0x5A5A;
  int16_t movement;

  yield();

  movement=accel_read();

  Serial.println(movement);

  switch (button_get_state()){
      case BUTTON_PRESS_NONE:
          break;
      case BUTTON_PRESS_SHORT:
          Serial.println("[BTN] SHORT");
          break;
      case BUTTON_PRESS_LONG:
          Serial.println("[BTN] LONG");
          break;
  }

  if (recvd_msg_flag) {

    if (recvd_msg.type == MSG_TYPE_JOIN) {

      Serial.print("Mensaje de JOIN recibido desde UUID ");
      Serial.print(recvd_msg.uuid);
      Serial.print(" al grupo ");
      Serial.println(recvd_msg.group);

      //Miramos a ver si el mensaje de JOIN ya lo habíamos recibido para ese UUID
      //También es importante controlar que un nodo no mande varias veces un mensaje de JOIN
      if (!game_search_player(recvd_msg.uuid, num_players)) {
        game_add_player(recvd_msg.uuid);
      }

    } else if (recvd_msg.type == MSG_TYPE_START) {

      Serial.print("Mensaje de START recibido desde UUID ");
      Serial.print(recvd_msg.uuid);
      Serial.print(" al grupo ");
      Serial.println(recvd_msg.group);

    } else if (recvd_msg.type == MSG_TYPE_DEAD) {

      Serial.print("Mensaje de DEAD recibido desde UUID ");
      Serial.print(recvd_msg.uuid);
      Serial.print(" al grupo ");
      Serial.println(recvd_msg.group);

      //Aquí meter el control de que cuando sólo quede un jugador se llame a la función que resetea el juego después de una secuencia de luces o algo así

    }

    recvd_msg_flag=false;

  }

  //utils_test_sender(group);


}

