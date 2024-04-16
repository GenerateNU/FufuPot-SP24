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
#ifndef MOTOR
    #define MOTOR
    #include "motor.h"
#endif

#ifndef WINDOWS_H
    #define WINDOWS_H
    #include <Windows.h>
#endif

#define soft_cook_time 6969;
#define reg_cook_time 69420;
#define firm_cook_time 420420;

/**
 * Enumeration for which cooking cycle to do
*/
enum cooking_type{soft, regular, firm};

/**
 * @brief cooks the fufu on the selected cycle
 * 
 * @param firmness dictates which cycle to use based on the enumeration given
*/
void cook(cooking_type firmness);
