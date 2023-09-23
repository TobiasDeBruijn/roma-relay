#ifndef ROMA_RELAY_RELAY_H
#define ROMA_RELAY_RELAY_H

#include <stdbool.h>

typedef enum Relay {
    Relay1,
    Relay2
} Relay;

void enable_relay(Relay relay, bool enabled);
void toggle_relay(Relay relay);

#endif //ROMA_RELAY_RELAY_H
