#ifndef __OUSTPE_H
#define __OUSTPE_H


enum msg_type{
  MSG_TYPE_JOIN,
  MSG_TYPE_START,
  MSG_TYPE_DEAD
};

typedef struct __attribute__((packed)) esp_now_msg_t {
  uint16_t type;
  uint32_t uuid;
  uint16_t group;
} esp_now_msg_t;


#endif
