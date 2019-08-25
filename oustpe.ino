#include <WiFi.h>
#include <esp_now.h>
#include <stdint.h>
#include <string.h>

#include "oustpe.h"
#include "button.h"

#define WIFI_CHANNEL    1
#define LED_PIN         18
#define PULSADOR        15

boolean recvd_msg_flag;
esp_now_msg_t recvd_msg;

void setup() {
  Serial.begin(115200);
  Serial.println("Arrancando");

  pinMode(LED_PIN, OUTPUT);

  accel_config();

  espnow_network_setup();

  game_set_uuid(utils_get_chip_id());

}


void loop() {
  int16_t movement;

  yield();


  // controles
  switch (button_get_state()) {
      case BUTTON_PRESS_NONE:
          break;
      case BUTTON_PRESS_SHORT:
          Serial.println("[BTN] SHORT");
          if (game_state == GAME_INITIAL || (game_state == GAME_ENDED && !num_players_alive)) game_join();
          break;
      case BUTTON_PRESS_LONG:
          Serial.println("[BTN] LONG");
          if (game_state == GAME_JOINED) game_start();
          //if (game_state == GAME_ENDED) game_reset();
          break;
  }

  // Control de la muerte
  if (movement=accel_read() > THRESHOLD){
      Serial.print("DEMASIADO MOVIMIENTO!!!! ");
      Serial.println(movement);
      //(uint16_t m_type, uint32_t m_uuid, uint16_t m_group)
      protocol_send_cmd(MSG_TYPE_DEAD, my_uuid, my_group);
  }


  if (recvd_msg_flag) {

    if (recvd_msg.type == MSG_TYPE_JOIN) {

      // *** si se recibe un JOIN, pero estamos a mitad de partida, ignorar

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

      // alguien ha muerto!
      num_players_alive--;

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

