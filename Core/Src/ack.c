#include <memory.h>
#include <stdlib.h>
#include "ack.h"
#include "stm32l1xx_hal.h"

AckManager init_ackmanager() {
  AckManager manager = {
          .isExpectingAnyAck = false,
          .lastExpectingAckIndex = 0,
  };

  return manager;
}

Ack create_ack(uint16_t ackId, const uint8_t* data, uint8_t len) {
  Ack ack = {
          .ackId = ackId,
          .datalen = len,
  };

  memcpy(ack.data, data, len);

  return ack;
}

void add_ack(AckManager* manager, Ack ack) {
  InternalAck internalAck = {
          .ack = ack,
          .retryAt = 0,
          .retries = 0,
  };

  if(!manager->isExpectingAnyAck) {
    manager->isExpectingAnyAck = true;
    manager->expectedAcks[0] = internalAck;

    return;
  }

  if(manager->lastExpectingAckIndex + 1 > MaxAcks) {
    return;
  }

  manager->expectedAcks[++manager->lastExpectingAckIndex] = internalAck;
}

bool has_ack(AckManager* manager, uint16_t ackId) {
  if(!manager->isExpectingAnyAck) {
    return false;
  }

  for(uint8_t i = 0; i < manager->lastExpectingAckIndex; i++) {
    InternalAck ack = manager->expectedAcks[i];
    if (ack.ack.ackId == ackId) {
      return true;
    }
  }

  return false;
}

int get_pending_acks(AckManager* manager, Ack* out) {
  if(!manager->isExpectingAnyAck) {
    return 0;
  }

  uint8_t bufferIndex = 0;

  for(int i = 0; i <= manager->lastExpectingAckIndex; i++) {
    InternalAck iAck = manager->expectedAcks[i];

    if(iAck.retryAt >= HAL_GetTick()) {
      out[bufferIndex++] = iAck.ack;
    }
  }

  return bufferIndex;
}

void remove_ack(AckManager* manager, uint16_t ackId) {
  if(!manager->isExpectingAnyAck) {
    return;
  }

  for(uint8_t i = 0; i < manager->lastExpectingAckIndex; i++) {
    InternalAck ack = manager->expectedAcks[i];
    if(ack.ack.ackId == ackId) {
      // Shift over all elements to replace the current one if necessary
      if(i == manager->lastExpectingAckIndex) {
        // Its the last element, no shifting necessary
        if(manager->lastExpectingAckIndex == 0) {
          manager->isExpectingAnyAck = false;
        } else {
          manager->lastExpectingAckIndex--;
        }

        for(uint8_t j = i; j < manager->lastExpectingAckIndex; j++) {
          manager->expectedAcks[j] = manager->expectedAcks[j + 1];
        }

        if(manager->lastExpectingAckIndex == 0) {
          manager->isExpectingAnyAck = false;
        } else {
          manager->lastExpectingAckIndex--;
        }
        return;
      }
    }
  }
}

uint16_t generate_ack_id() {
  return (uint16_t) (rand() >> 16);
}