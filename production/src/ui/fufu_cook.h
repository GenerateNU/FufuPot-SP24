#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"
#include "hardware/pwm.h"
#include "pico/binary_info.h"
#include "heat_ctrl.h"
#include "pin_definitions.h"
#include "heat_func.h"
#include "water_pump.h"

void soft_cook();

void reg_cook();

void firm_cook();