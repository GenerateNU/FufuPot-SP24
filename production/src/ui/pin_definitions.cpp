#include "pin_definitions.h"


void initialize_gpios() {
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
    gpio_init(watersense_2_read);
    gpio_init(watersense_1_read);
    gpio_init(gpio_24);
    gpio_init(gpio_25);
    gpio_init(gpio_26);
    gpio_init(gpio_27);
    gpio_init(sda_ext);
    gpio_init(scl_ext);
}

void set_gpio_funcs() {
    //water pins
    gpio_set_dir(pump_en, 1);
    gpio_set_dir(watersense_2_read, 0);
    gpio_set_dir(watersense_1_read, 0);

    //LED
    gpio_set_dir(hot_led_pos, 1);

    //motor 
    gpio_set_dir(motor_en, 1);
    gpio_set_dir(motor_dir, 1);
    //Sets motor to counterclockwise
    gpio_put(motor_dir, 0);
    gpio_set_function(motor_pwm, GPIO_FUNC_PWM);


    //heating pins
    gpio_set_function(heat_pwm, GPIO_FUNC_PWM);
}

uint32_t pwm_set_freq_duty(int slice_num, int chan, uint32_t f, int d) {
    uint32_t clock = 12000000;
    uint32_t divider16 = clock / f / 4096 + (clock % (f * 4096) != 0);
    if (divider16 / 16 == 0) {
        divider16 = 16;
    }
    uint32_t wrap = clock * 16 / divider16 / f - 1;
    pwm_set_clkdiv_int_frac(slice_num, divider16/16, divider16 & 0xF);
    pwm_set_wrap(slice_num, wrap);
    pwm_set_chan_level(slice_num, chan, wrap * d / 100);
    return wrap;
}
