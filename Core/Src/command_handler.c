#include "rfm-protocol/include/command.h"
#include "relay.h"

void handle_command_on_off(struct CommandOnOff* onOff);

void execute_command_packet(CommandPacket* packet) {
  switch(packet->commandType) {
    case TypeOnOff: {
      handle_command_on_off(&packet->onOff);
      break;
    }
  }
}

void handle_command_on_off(struct CommandOnOff* onOff) {
  Relay relay;
  switch(onOff->relayIndex) {
    case 1:
      relay = Relay1;
      break;
    case 2:
      relay = Relay2;
      break;
  }

  enable_relay(relay, onOff->on);
}