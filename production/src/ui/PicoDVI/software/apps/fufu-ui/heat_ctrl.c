#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"
#include "hardware/pwm.h"
#include "pico/binary_info.h"

#define i2c_bus 0
#define IR_addr 0x36
#define PWM_PIN 31
#define LED_PIN 29
#define D_CYCLE 0.5

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

void heat_on(){
    
}

void heaf_off(){

}


int main() {
    gpio_init(PWM_PIN);
    //pio_set_dir(PWM_PIN, GPIO_OUT);
    gpio_set_function(PWM_PIN, GPIO_FUNC_PIN)
    // figure out how to set level
    //level = 

    // if one wanted to obtain PWM generator slice and channel values, it's as shown:
    //static uint   pwm_gpio_to_slice_num(uint gpio)
    //static uint   pwm_gpio_to_channel(uint gpio)
    //slice = pwm_gpio_to_slice_num (PWM_PIN); 
    //channel = pwm_gpio_to_channel (PWM_PIN);

    pwm_set_gpio_level(uint PWM_PIN, uint16_t level)
}