//
// Created by tobias on 24-9-23.
//

#ifndef ROMA_RELAY_ACK_H
#define ROMA_RELAY_ACK_H

#include <stdint.h>
#include <stdbool.h>

#define MaxAcks 16
#define MaxAckDataLen 32

typedef struct Ack {
    uint16_t ackId;
    uint8_t data[MaxAckDataLen];
} Ack;

typedef struct InternalAck {
    uint32_t retryAt;
    uint8_t retries;
    Ack ack;
} InternalAck;

typedef struct AckManager {
    bool isExpectingAnyAck;
    uint8_t lastExpectingAckIndex;
    InternalAck expectedAcks[MaxAcks];
} AckManager;

AckManager init_ackmanager();
Ack create_ack(uint16_t ackId, const uint8_t* data, uint8_t len);
void add_ack(AckManager* manager, Ack ack);
bool has_ack(AckManager* manager, uint16_t ackId);
void remove_ack(AckManager* manager, uint16_t ackId);

#endif //ROMA_RELAY_ACK_H
