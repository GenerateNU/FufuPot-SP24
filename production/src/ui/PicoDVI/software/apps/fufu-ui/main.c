#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "hardware/clocks.h"
#include "hardware/irq.h"
#include "hardware/sync.h"
#include "hardware/gpio.h"
#include "hardware/vreg.h"
#include "pico/sem.h"

#include "dvi.h"
#include "dvi_serialiser.h"
#include "common_dvi_pin_configs.h"
#include "sprite.h"

#include "raspberry_128x128_rgab5515.h"
#include "eben_128x128_rgab5515.h"

#define FRAME_WIDTH 400
#define FRAME_HEIGHT 240
#define VREG_VSEL VREG_VOLTAGE_1_20
#define DVI_TIMING dvi_timing_800x480p_60hz

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


struct dvi_inst dvi0;

void core1_main() {
	dvi_register_irqs_this_core(&dvi0, DMA_IRQ_0);
	while (queue_is_empty(&dvi0.q_colour_valid))
		__wfe();
	dvi_start(&dvi0);
	dvi_scanbuf_main_16bpp(&dvi0);
	__builtin_unreachable();
}

void heat_en(){
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

    level = ((1.25 * pow(10, 8)) / ((uint) pwm_freq) - 1) * ((float) pwm_duty);

    // if one wanted to obtain PWM generator slice and channel values, it's as shown:
    //static uint   pwm_gpio_to_slice_num(uint gpio)
    //static uint   pwm_gpio_to_channel(uint gpio)
    //slice = pwm_gpio_to_slice_num (PWM_PIN); 
    //channel = pwm_gpio_to_channel (PWM_PIN);

    pwm_set_gpio_level(uint8_t pwm_pin, uint16_t level);
	slice = pwm_gpio_to_slice_num (pwm_pin); 
}

int main() {


}