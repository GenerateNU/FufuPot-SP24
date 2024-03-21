#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"
#include "pico/binary_info.h"

#define i2c_bus 0
#define IR_addr 0x36
#define PWM_PIN 20
#define D_CYCLE 0.5

void check_temp(uint8_t upper_byte){

    // Check flags and raise alerts accordingly 
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

void heat_on(){

}

void heaf_off(){

}


int main() {
    pwm.freq(1000)
    gpio_init(PWM_PIN);
    gpio_set_dir(PWM_PIN, GPIO_OUT);
}

