#include "motor.h"



void motor_on(bool enabled) {
    //enable digital pin to motor 
    gpio_put(motor_en, enabled);
    //motor direction should already be set but just in case
    gpio_put(motor_dir, 0);

    // Find out which PWM slice is connected to GPIO 0 (it's slice 0)
    uint8_t slice = pwm_gpio_to_slice_num(motor_pwm);
    uint8_t chan = pwm_gpio_to_channel(motor_pwm);
    pwm_set_freq_duty(slice, chan, motor_pwm_freq, motor_pwm_duty);
    // Set the PWM running if enabled==true, turn the pwm signal off if enabled==false
    pwm_set_enabled(slice, enabled);
    /// \end::setup_pwm[]
}