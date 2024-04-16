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
#ifndef HEAT_FUNC
    #define HEAT_FUNC
    #include "heat_func.h"
#endif
#ifndef PIN_DEF
    #define PIN_DEF
    #include "pin_definitions.h"
#endif
#ifndef WATER_PUMP
    #define WATER_PUMP
    #include "water_pump.h"
#endif

#define soft_cook_time 6969;
#define reg_cook_time 69420;
#define firm_cook_time 420420;



/**
 * @brief cooks the fufu on the soft cycle using constants defined above
 **/
void soft_cook();

/**
 * @brief cooks the fufu on the regular cycle using constants defined above
 **/
void reg_cook();

/**
 * @brief cooks the fufu on the hard cycle using constants defined above
 **/
void firm_cook();