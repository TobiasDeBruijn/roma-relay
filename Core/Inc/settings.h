//
// Created by tobias on 25-9-23.
//

#ifndef ROMA_RELAY_SETTINGS_H
#define ROMA_RELAY_SETTINGS_H

#include <stdbool.h>
#include "stm32l1xx.h"
#include "ack.h"
#include "include/rfm69.h"

typedef struct DeviceSettings {
    bool relay1DefaultOn;
    bool relay2DefaultOn;
} DeviceSettings;

HAL_StatusTypeDef request_settings(AckManager* ackManager, RFM69* rfm);

#endif //ROMA_RELAY_SETTINGS_H
