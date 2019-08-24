

boolean game_search_player(uint32_t id, byte num_players){
  for (byte i=0; i<num_players; i++){
    if (id == players[i]) {
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

  players[num_players-1]=id;
  num_players++;

}

//Resetea el juego y borra todos los jugadores
void game_reset(){

}
