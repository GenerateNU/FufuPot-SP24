#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"
#include "pico/binary_info.h"

#define i2c_bus 0
#define IR_addr 0x36
#define PWM_PIN 20
#define FREQ 20000
#define D_CYCLE 0.5

int read_temp(uint8_t IR_addr, ){
    
}

int main() {
    gpio_init(PWM_PIN);
    gpio_set_dir(PWM_PIN, GPIO_OUT);
}

