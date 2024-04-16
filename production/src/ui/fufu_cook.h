#include <stdio.h>
#include <stdlib.h>
#include <pico/stdlib.h>
#include <hardware/gpio.h>
#include <hardware/i2c.h>
#include <hardware/pwm.h>
#include <pico/binary_info.h>

#include "heat_func.h"
#include "pin_definitions.h"
#include "heat_func.h"
#include "water_pump.h"

#define soft_cook_time 6969;
#define reg_cook_time 69420;
#define firm_cook_time 420420;

/**
 * @brief cooks the fufu on the soft cycle using constants defined above
 **/
void soft_cook();

/**
 * @brief cooks the fufu on the regular cycle using constants defined above
 **/
void reg_cook();

/**
 * @brief cooks the fufu on the hard cycle using constants defined above
 **/
void firm_cook();