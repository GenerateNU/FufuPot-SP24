#include "pin_definitions.h"

void initialize_pins() {
    gpio_init(gpio_0);
    gpio_init(motor_en);
    gpio_init(piezo_en);
    gpio_init(motor_dir);
    gpio_init(motor_pwm);
    gpio_init(gpio_4);
    gpio_init(gpio_5);
    gpio_init(gpio_6);
    gpio_init(dvi_d2_pos);
    gpio_init(dvi_d2_neg);
    gpio_init(dvi_d1_pos);
    gpio_init(dvi_d1_neg);
    gpio_init(dvi_d0_pos);
    gpio_init(dvi_d0_neg);
    gpio_init(dvi_ck_pos);
    gpio_init(dvi_ck_neg);
    gpio_init(gpio_7);
    gpio_init(gpio_8);
    gpio_init(hot_led_pos);
    gpio_init(gpio_19);
    gpio_init(heat_pwm);
    gpio_init(pump_en);
    gpio_set_dir(pump_en, 1);
    gpio_init(watersense_2_read);
    gpio_set_dir(watersense_2_read, 0);
    gpio_init(watersense_1_read);
    gpio_set_dir(watersense_1_read, 0);
    gpio_init(gpio_24);
    gpio_init(gpio_25);
    gpio_init(gpio_26);
    gpio_init(gpio_27);
    gpio_init(sda_ext);
    gpio_init(scl_ext);
}