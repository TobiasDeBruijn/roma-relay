#include "rfm-protocol/include/command.h"
#include "config.h"
#include "relay.h"
#include "ack.h"

void handle_command_on_off(struct OnOff* onOff);

void handle_command_packet(CommandPacket* packet) {
  if(packet->serialNumber != SerialNumber) {
    return;
  }

  switch(packet->commandType) {
    case TypeOnOff: {
      handle_command_on_off(&packet->onOff);
      break;
    }
  }

  add_ack(create_ack())
  // TODO send out ACK
}

void handle_command_on_off(struct OnOff* onOff) {
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