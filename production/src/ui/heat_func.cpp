#include "heat_func.h"

float convert_temp(uint8_t pin_sda, uint8_t pin_scl) {

    // This is placeholder code
    // This function will convert raw data from IR sensor and
    // make it useful to program

    // This will change depending on how IR sensor returns data
    // Function will also compensate for sensor inaccuracy

    float temperature;
    uint8_t buf[2];
    i2c_read_blocking(i2c_bus, ir_addr, buf, 2, false);
    uint16_t upper_byte = buf[0];
    uint16_t lower_byte = buf[1];

    if ((upper_byte & 0x10) == 0x10) {
        upper_byte = upper_byte & 0x0F;
        temperature = 256 - (((float) upper_byte * 16) + ((float) lower_byte / 16));
    } else {
        temperature = (((float) upper_byte * 16) + ((float) lower_byte / 16));
    }
    return temperature;
}

uint16_t check_temp(float temp){

    // Check temp limits and raise alerts accordingly 
    // temperature limits subject to change
    // Return result
    
    if (temp >= 100) { //TACTUAL > TUPPER

        // lower frequency to reduce temp

        uint8_t freq_pwm = 9000;
        float level = ((1.25 * pow(10, 8)) / ((uint) pwm_freq) - 1) * ((float) pwm_duty);
        return level;
    }
    if (temp <= 50) { //TACTUAL < TLOWER

        // raise frequency to increase temp

        uint pwm_freq = 11000;
        level = ((1.25 * pow(10, 8)) / ((uint) pwm_freq) - 1) * ((float) pwm_duty);
        return level;
    }
    if (temp == 150) { //TACTUAL > TCRIT

        // set pwm duty to 0%

        uint pwm_duty = 0 ;
        level = ((1.25 * pow(10, 8)) / ((uint) pwm_freq) - 1) * ((float) pwm_duty);
        return level;
    }
}


void heat_on(bool enabled){
    // Find out which PWM slice is connected to GPIO 0 (it's slice 0)
    uint8_t slice = pwm_gpio_to_slice_num(heat_pwm);
    uint8_t chan = pwm_gpio_to_channel(heat_pwm);
    pwm_set_freq_duty(slice, chan, heat_pwm_freq, 50);
    // Set the PWM running if enabled==true, turn the pwm signal off if enabled==false
    pwm_set_enabled(slice, enabled);
    /// \end::setup_pwm[]
}

void heat_led_on(bool enabled){
    gpio_put(hot_led_pos, enabled);
}
