#include "water_pump.h"

bool is_water_full() {
  return gpio_is_pulled_up(watersense_1_read);
}

bool is_water_not_empty() {
  return gpio_is_pulled_up(watersense_2_read);
}

void pump_water(bool enabled) {
  gpio_put(pump_en, enabled);
}