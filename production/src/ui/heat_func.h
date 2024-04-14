#include <stdio.h>
#include <stdlib.h>
#include <pico/stdlib.h>
#include <hardware/gpio.h>
#include <hardware/i2c.h>
#include <hardware/pwm.h>
#include <pico/binary_info.h>

#include "pin_definitions.h"

#define i2c_bus 0
#define sda_pin 28
#define scl_pin 29
#define pwm_pin 31
#define led_pin 29
#define d_cycle 0.5
#define pwm_duty 0.5
#define pwm_freq 10000

//i2c bus address
#define ir_addr 0x36

//hardware registers (none yet):



float convert_temp(uint8_t pin_sda, uint8_t pin_scl);

uint16_t check_temp(float temp);

uint32_t pwm_set_freq_duty(int slice_num,
       int chan,uint32_t f, int d);

void heat_on(bool enabled);