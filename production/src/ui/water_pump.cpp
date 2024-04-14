#include "water_pump.h"

bool is_water_full() {
  return gpio_is_pulled_up(watersense_1_read);
}

bool is_water_not_empty() {
  return gpio_is_pulled_up(watersense_2_read);
}

void start_pumping() {
  gpio_put(pump_en, 1);
}

void stop_pumping() {
  gpio_put(pump_en, 0);
}