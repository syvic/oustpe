#include "oustpe.h"

//Resetea el juego y borra todos los jugadores
void game_reset() {
  num_players=num_players_alive=1;
}

void game_set_uuid(uint32_t uuid) {
  my_uuid=uuid;
}

void game_send_command(uint16_t type) {
  esp_now_msg_t msg;
  msg.type=type;
  msg.uuid=my_uuid;
  msg.group=my_group;
  espnow_send_msg(&msg);
}

void game_join() {
  game_send_command(MSG_TYPE_JOIN);
  game_state=GAME_JOINED;
}

void game_start() {
  num_players_alive=num_players;
  game_send_command(MSG_TYPE_START);
  game_state=GAME_STARTED;
}

void game_dead() {
  game_send_command(MSG_TYPE_DEAD);
  game_state=GAME_ENDED;
  num_players_alive--;
}

boolean game_search_player(uint32_t id, byte num_players){
  for (byte i=0; i<num_players; i++){
    if (id == players[i].uuid) {
      Serial.println("ID Encontrado");
      return 1;
    }
  }
  Serial.print("ID no encontrado. ");
  return 0;
}

void game_add_player(uint32_t id){
  Serial.print("Insertando jugador ");
  Serial.print(id, HEX);
  Serial.print(" en posición ");
  Serial.println(num_players);

  player_t *player=&players[num_players-1];
  player->uuid=id;
  player->dead=false;
  num_players++;

}

