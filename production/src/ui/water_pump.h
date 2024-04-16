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
#ifndef PIN_DEF
    #define PIN_DEF
    #include "pin_definitions.h"
#endif

/**
 * @returns true if the sensor detecting full water level is reporting high, 
 * AKA true if water is past the full point
 */
bool is_water_full();

/**
 * @returns true if the sensor detecting empty water level is reporting high, 
 * AKA true if water is past the empty point
 */
bool is_water_not_empty();

/**
 * @brief sets pump pin to high/low, turning the pump on/off
 * 
 * @param enabled when true, turns pump on, when false, turns pump off
 */
void pump_water(bool enabled);
