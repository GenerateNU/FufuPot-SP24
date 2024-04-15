#include <stdio.h>
#include <stdlib.h>
#include <rp2_common/hardware_gpio/include/hardware/gpio.h>
#include <hardware/i2c.h>
#include <hardware/pwm.h>
#include <pico/binary_info.h>

#include "pin_definitions.h"

//

/**
 * @returns true if the sensor detecting full water level is reporting high, 
 * AKA true if water is past the full point
 */
bool is_water_full();

/**
 * @returns true if the sensor detecting empty water level is reporting high, 
 * AKA true if water is past the empty point
 */
bool is_water_not_empty();

/**
 * @brief sets pump pin to high, turning the pump on
 */
void start_pumping();

/**
 * @brief sets pump pin to high, turning the pump off
 */
void stop_pumping();