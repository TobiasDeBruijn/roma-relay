#include "settings.h"
#include "rfm-protocol/include/settings.h"
#include "config.h"

SettingsPacket constructRequest() {
  SettingsPacket packet;
  packet.serialNumber = SerialNumber;
  packet.ackId = generate_ack_id();
  packet.flags = SettingsPacket_Flag_isRequest;

  return packet;
}

HAL_StatusTypeDef request_settings(AckManager* ackManager, RFM69* rfm) {
  uint8_t buffer[16];

  SettingsPacket request = constructRequest();
  int length = serialize_settings(buffer, &request);

  HAL_StatusTypeDef result = send(rfm, RfmOwnId, RfmGatewayId, buffer, length);
  if(result != HAL_OK) {
    return result;
  }

  add_ack(ackManager, create_ack(request.ackId, buffer, length));
  return HAL_OK;
}