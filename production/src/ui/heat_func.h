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
#define pwm_duty_heat 50 
#define pwm_freq 10000

//GLOBAL TESTING VARIABLES
#define heat_pwm_freq 2500
#define motor_pwm_freq 250 //3kHz or 4kHz is "100% Speed"

//i2c bus address
#define ir_addr 0x36

//hardware registers (none yet):



float convert_temp(uint8_t pin_sda, uint8_t pin_scl);

uint16_t check_temp(float temp);

/*
 * @brief turns on/off the heat pwm signal 
 * 
 * @param enabled true if the signal is to be turned on, false to turn off
*/
void heat_on(bool enabled);

/*
 * @brief turns on/off the heat LED  
 * 
 * @param enabled true if the LED is to be turned on, false to turn off
*/
void heat_led_on(bool enabled);
