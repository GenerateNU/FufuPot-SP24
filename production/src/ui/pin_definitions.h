#ifndef HARDWARE_GPIO_H
    #define HARDWARE_GPIO_H
    #include <rp2_common/hardware_gpio/include/hardware/gpio.h>
#endif
#ifndef HARDWARE_PWM_H
    #define HARDWARE_PWM_H
    #include <hardware/pwm.h>
#endif
#ifndef CSTDINT_H
    #define CSTDINT_H   
    #include <cstdint>
#endif

//unused gpio pin, pin 0 on MCU, commented out due to switching the motor pin
//#define gpio_0 0
//digital gpio for enabling the motor (HIGH = motor can spin), pin 1 on the MCU
#define motor_en 1
//digital gpio for enabling the buzzer, pin 2 on the MCU
#define piezo_en 2
//digital gpio for the direction of the motor (HIGH = cw, LOW = ccw), pin 3 on the MCU
#define motor_dir 3
//pin for spinning the motor, sends a PWM signal, pin 0 on the MCU, PWM0 A on RP2040
#define motor_pwm 0
//unused gpio pin, pin 5 on MCU
#define gpio_4 5
//unused gpio pin, pin 6 on MCU
#define gpio_5 6
//unused gpio pin, pin 7 on MCU
#define gpio_6 7
//DVI pin, leo knows what it does, pin 8 on MCU
#define dvi_d2_pos 8
//DVI pin, leo knows what it does, pin 9 on MCU
#define dvi_d2_neg 9
//DVI pin, leo knows what it does, pin 10 on MCU
#define dvi_d1_pos 10
//DVI pin, leo knows what it does, pin 11 on MCU
#define dvi_d1_neg 11
//DVI pin, leo knows what it does, pin 12 on MCU
#define dvi_d0_pos 12
//DVI pin, leo knows what it does, pin 13 on MCU
#define dvi_d0_neg 13
//DVI pin, leo knows what it does, pin 14 on MCU
#define dvi_ck_pos 14
//DVI pin, leo knows what it does, pin 15 on MCU
#define dvi_ck_neg 15
//unused gpio pin, pin 16 on MCU
#define gpio_7 16
//unused gpio pin, pin 17 on MCU
#define gpio_8 17
#define hot_led_pos 18
//unused gpio pin, pin 19 on MCU
#define gpio_19 19
//pin for power the heating circuit, sends a PWM signal, pin 20 on the MCU, PWM2 A on RP2040
#define heat_pwm 20
//digital gpio for enabling the pump (HIGH = water flowing), pin 21 on the MCU
#define pump_en 21
//digital input from the empty water sensor (HIGH = water present), pin 22 on the MCU
#define watersense_2_read 22
//digital input from the full water sensor (HIGH = water present), pin 22 on the MCU
#define watersense_1_read  23
//unused gpio pin, pin 24 on MCU
#define gpio_24 24
//unused gpio pin, pin 25 on MCU
#define gpio_25 25
//unused gpio pin (has ADC also), pin 26 on MCU
#define gpio_26 26
//unused gpio pin (has ADC also), pin 27 on MCU
#define gpio_27 27
//serial data line for I2C capability
#define sda_ext 28
//serial clock line for I2C capability
#define scl_ext 29

/**
 * @brief initialize gpio pins using gpio_init
 */
void initialize_gpios();

/**
 * @brief set functions of all gpio pins
 */
void set_gpio_funcs();

/*
 * @brief 
 * 
 * @param slice_num number passed from the GPIO to slice converter
 * @param chan number passed from the GPIO to channel converter
 * @param f frequency of the PWM signal
 * @param d duty cycle of the PWM signal
 * 
 * @return returns the wrap value of the PWM signal
*/
uint32_t pwm_set_freq_duty(int slice_num, int chan, uint32_t f, int d);