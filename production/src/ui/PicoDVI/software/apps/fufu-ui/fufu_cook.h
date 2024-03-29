#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"
#include "hardware/pwm.h"
#include "pico/binary_info.h"
#include "heat_ctrl.h"

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


void heat_on(bool enabled){
#if !defined(i2c_default) || !defined(PICO_DEFAULT_I2C_SDA_PIN) || !defined(PICO_DEFAULT_I2C_SCL_PIN)
    #warning i2c / bmp280_i2c example requires a board with I2C pins
        puts("Default I2C pins were not defined");
    return 0;
#else
    i2c_init(i2c0, 100 * 1000);
    gpio_init(pwm_pin);
    gpio_pull_up(sda_pin);
    gpio_pull_up(scl_pin);

    //pio_set_dir(PWM_PIN, GPIO_OUT);
    gpio_set_function(pwm_pin, GPIO_FUNC_PWM);

    level = ((1.25 * pow(10, 8)) / ((uint) pwm_freq) - 1) * ((float) pwm_duty);

    // if one wanted to obtain PWM generator slice and channel values, it's as shown:
    //static uint   pwm_gpio_to_slice_num(uint gpio)
    //static uint   pwm_gpio_to_channel(uint gpio)
    //slice = pwm_gpio_to_slice_num (PWM_PIN); 
    //channel = pwm_gpio_to_channel (PWM_PIN);
    
    pwm_set_gpio_level(uint8_t pwm_pin, uint16_t level);
	slice = pwm_gpio_to_slice_num(pwm_pin);
    pwm_set_enabled(slice, enabled);
}