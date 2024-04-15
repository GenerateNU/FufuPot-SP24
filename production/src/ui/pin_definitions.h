#include <rp2_common/hardware_gpio/include/hardware/gpio.h>

#define gpio_0 0
#define motor_en 1
#define piezo_en 2
#define motor_dir 3
#define motor_pwm 4
#define gpio_4 5
#define gpio_5 6
#define gpio_6 7
#define dvi_d2_pos 8
#define dvi_d2_neg 9
#define dvi_d1_pos 10
#define dvi_d1_neg 11
#define dvi_d0_pos 12
#define dvi_d0_neg 13
#define dvi_ck_pos 14
#define dvi_ck_neg 15
#define gpio_7 16
#define gpio_8 17
#define hot_led_pos 18
#define gpio_19 19
#define heat_pwm 20
#define pump_en 21
#define watersense_2_read 22
#define watersense_1_read  23
#define gpio_24 24
#define gpio_25 25
#define gpio_26 26
#define gpio_27 27
#define sda_ext 28
#define scl_ext 29

/**
 * @brief initialize gpio pins using gpio_init
 */
void initialize_gpios();

/**
 * @brief set functions of all gpio pins
 */
void set_gpio_funcs();