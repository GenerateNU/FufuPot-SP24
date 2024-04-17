#ifndef STDIO_H
    #define STDIO_H
    #include <stdio.h>
#endif
#ifndef STDLIB_H
    #define STDLIB_H
    #include <stdlib.h>
#endif
#ifndef PICO_STDLIB_H
    #define PICO_STDLIB_H
    #include <pico/stdlib.h>
#endif
#ifndef HARDWARE_GPIO_H
    #define HARDWARE_GPIO_H
    #include <rp2_common/hardware_gpio/include/hardware/gpio.h>
#endif
#ifndef HARDWARE_PWM_H
    #define HARDWARE_PWM_H
    #include <hardware/pwm.h>
#endif
#ifndef HARDWARE_I2C_H
    #define HARDWARE_I2C_H
    #include <hardware/i2c.h>
#endif
#ifndef PICO_BINARY_H
    #define PICO_BINARY_H
    #include <pico/binary_info.h>
#endif

#ifndef PIN_DEF
    #define PIN_DEF
    #include "pin_definitions.h"
#endif

//should be the number of the i2c bus being used, not implemented at the moment
#define i2c_bus 0
//duty cycle of the pwm for the heat, cannot exceed 65
#define pwm_duty_heat 58

//GLOBAL TESTING VARIABLES
#define heat_pwm_freq 2500


//i2c bus address
#define ir_addr 0x36

//hardware registers (none yet):

/**
float convert_temp(uint8_t pin_sda, uint8_t pin_scl);

uint16_t check_temp(float temp);
*/

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


