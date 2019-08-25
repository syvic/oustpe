#include "oustpe.h"

void protocol_send_cmd(uint16_t m_type, uint32_t m_uuid, uint16_t m_group) {
    esp_now_msg_t msg;


    Serial.printf("[PROTO] <%d> Enviando mensaje tipo %X desde UUID %X al grupo %X\n", millis(), m_type, m_uuid, m_group);

    //Comprobamos el tipo de mensaje
    if (m_type != MSG_TYPE_JOIN && m_type != MSG_TYPE_START && m_type != MSG_TYPE_DEAD) return;

    msg.type = m_type;
    msg.uuid = m_uuid;
    msg.group = m_group;

    //Enviamos el mensaje tres veces para garantizar la entrega
    for (byte i=0; i<3; i++){
        espnow_send_msg(&msg);
        delay(random(1,20));
    }

}
