#ifndef __OUSTPE_H
#define __OUSTPE_H

#define MAX_PLAYERS     64
#define THRESHOLD       512


enum game_states {
  GAME_INITIAL,
  GAME_JOINED,
  GAME_STARTED,
  GAME_ENDED
};

enum msg_type {
  MSG_TYPE_JOIN,
  MSG_TYPE_START,
  MSG_TYPE_DEAD
};

typedef struct __attribute__((packed)) esp_now_msg_t {
  uint16_t type;
  uint32_t uuid;
  uint16_t group;
} esp_now_msg_t;

uint32_t my_uuid;
uint16_t my_group=0x5A5A;

int game_state=GAME_INITIAL;
static byte num_players=1;
static byte num_players_alive=1;

uint32_t players[MAX_PLAYERS];

#endif
