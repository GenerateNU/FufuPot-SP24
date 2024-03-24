#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"
#include "hardware/pwm.h"
#include "pico/binary_info.h"

#define i2c_bus 0
#define pwm_pin 31
#define led_pin 29
#define d_cycle 0.5
#define pwm_duty 0.5
#define pwm_freq 10000

//i2c bus address
#define ir_addr 0x36

//hardware registers (none yet):
//test

void check_temp(uint8_t upper_byte){

    // Check temp limits and raise alerts accordingly 
    // temperature limits subject to change
    if ((upper_byte & 0x40) == 0x40) { //TACTUAL > TUPPER
        heat_off();
        printf("Temperature is above the upper temperature limit.\n");
    }
    if ((upper_byte & 0x20) == 0x20) { //TACTUAL < TLOWER
        heat_on();
        printf("Temperature is below the lower temperature limit.\n");
    }
    if ((upper_byte & 0x80) == 0x80) { //TACTUAL > TCRIT
        printf("Temperature is above the critical temperature limit.\n");    
        exit();
    }
}

float convert_temp(uint8_t upper_byte, uint8_t lower_byte) {

    float temperature;

    if ((upper_byte & 0x10) == 0x10) {
        upper_byte = upper_byte & 0x0F;
        temperature = 256 - (((float) upper_byte * 16) + ((float) lower_byte / 16));
    } else {
        temperature = (((float) upper_byte * 16) + ((float) lower_byte / 16));
    }

    return temperature;
}

void heat_on(uint8_t slice){
    
}

void heaf_off(){

}


int main() {

    gpio_init(pwm_pin);
    //pio_set_dir(PWM_PIN, GPIO_OUT);
    gpio_set_function(pwm_pin, GPIO_FUNC_PIN)

    level = ((1.25 * pow(10, 8)) / ((uint) pwm_freq) - 1) * ((float) pwm_duty)

    // if one wanted to obtain PWM generator slice and channel values, it's as shown:
    //static uint   pwm_gpio_to_slice_num(uint gpio)
    //static uint   pwm_gpio_to_channel(uint gpio)
    //slice = pwm_gpio_to_slice_num (PWM_PIN); 
    //channel = pwm_gpio_to_channel (PWM_PIN);

    pwm_set_gpio_level(uint8_t pwm_pin, uint16_t level)
}