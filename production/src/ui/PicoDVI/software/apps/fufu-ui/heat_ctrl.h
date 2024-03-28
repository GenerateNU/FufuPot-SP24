#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"
#include "hardware/pwm.h"
#include "pico/binary_info.h"

float convert_temp(uint8_t upper_byte, uint8_t lower_byte) {

    // This is placeholder code
    // Will change depending on how IR sensor returns data
    // Function will also compensate for sensor inaccuracy

    float temperature;

    if ((upper_byte & 0x10) == 0x10) {
        upper_byte = upper_byte & 0x0F;
        temperature = 256 - (((float) upper_byte * 16) + ((float) lower_byte / 16));
    } else {
        temperature = (((float) upper_byte * 16) + ((float) lower_byte / 16));
    }

    return temperature;
}

void check_temp(uint8_t upper_byte){

    // Check temp limits and raise alerts accordingly 
    // temperature limits subject to change
    if ((upper_byte & 0x40) == 0x40) { //TACTUAL > TUPPER
        printf("Temperature is above the upper temperature limit.\n");
    }
    if ((upper_byte & 0x20) == 0x20) { //TACTUAL < TLOWER
        printf("Temperature is below the lower temperature limit.\n");
    }
    if ((upper_byte & 0x80) == 0x80) { //TACTUAL > TCRIT
        printf("Temperature is above the critical temperature limit.\n");    
        // power off?
        exit();
    }
    if ()
}

void heat_on(uint8_t slice){
    
}

void heaf_off(){

}