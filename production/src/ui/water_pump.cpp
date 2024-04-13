#include "water_pump.h"

bool is_water_full() {
  return gpio_is_pulled_up(watersense_1_read);
}