#include <stdbool.h>
#include "relay.h"
#include "main.h"

GPIO_TypeDef* relay_port(Relay relay){
  switch(relay) {
    case Relay1: return Relay1_GPIO_Port;
    case Relay2: return Relay2_GPIO_Port;
  }
}

uint16_t relay_pin(Relay relay) {
  switch(relay) {
    case Relay1: return Relay1_Pin;
    case Relay2: return Relay2_Pin;
  }
}

void enable_relay(Relay relay, bool enabled) {
  GPIO_PinState pinState = enabled ? GPIO_PIN_SET : GPIO_PIN_RESET;
  HAL_GPIO_WritePin(relay_port(relay), relay_pin(relay), pinState);
}

void toggle_relay(Relay relay) {
  HAL_GPIO_TogglePin(relay_port(relay), relay_pin(relay));
}
