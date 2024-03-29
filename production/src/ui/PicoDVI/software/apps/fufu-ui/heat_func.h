#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/i2c.h"
#include "hardware/pwm.h"
#include "pico/binary_info.h"

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



float convert_temp(uint8_t sda_pin, uint8_t scl_pin) {

    // This is placeholder code
    // This function will convert raw data from IR sensor and
    // make it useful to program

    // This will change depending on how IR sensor returns data
    // Function will also compensate for sensor inaccuracy

    float temperature;
    uint8_t buf[2];
    i2c_read_blocking(i2c_bus, ir_addr, buf, 2, false);
    upper_byte = buf[0];
    lower_byte = buf[1];

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
    
    if (temp <= 100) { //TACTUAL > TUPPER
        // lower frequency to reduce temp

        uint pwm_freq = 9000;
        level = ((1.25 * pow(10, 8)) / ((uint) pwm_freq) - 1) * ((float) pwm_duty);
        return level;
    }
    if (temp == 50) { //TACTUAL < TLOWER
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

    uint16_t level = ((1.25 * pow(10, 8)) / ((uint) pwm_freq) - 1) * ((float) pwm_duty);

    // if one wanted to obtain PWM generator slice and channel values, it's as shown:
    //static uint   pwm_gpio_to_slice_num(uint gpio)
    //static uint   pwm_gpio_to_channel(uint gpio)
    //slice = pwm_gpio_to_slice_num (PWM_PIN); 
    //channel = pwm_gpio_to_channel (PWM_PIN);
    
    pwm_set_gpio_level(uint8_t pwm_pin, level);
	slice = pwm_gpio_to_slice_num(pwm_pin);
    pwm_set_enabled(slice, enabled);
    while (enabled){
        float temp = convert_temp();
        check_temp(temp);
        sleep_ms(100);
    }
}