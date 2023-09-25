//
// Created by tobias on 24-9-23.
//

#ifndef ROMA_RELAY_COMMAND_HANDLER_H
#define ROMA_RELAY_COMMAND_HANDLER_H

#include "rfm-protocol/include/command.h"

void execute_command_packet(CommandPacket* packet);

#endif //ROMA_RELAY_COMMAND_HANDLER_H
