#include <stdio.h>
#include <stdlib.h>
#include <pico/stdlib.h>
#include <hardware/gpio.h>
#include <hardware/i2c.h>
#include <hardware/pwm.h>
#include <pico/binary_info.h>

#include "pin_definitions.h"

//returns true if the sensor detecting full water level is reporting high, 
//aka true if water is past the full point
bool is_water_full();

//returns true if the sensor detecting near empty water level is reporting high, 
//aka true if water past the empty point
bool is_water_not_empty();