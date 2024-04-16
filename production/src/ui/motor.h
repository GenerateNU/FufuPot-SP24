#ifndef PIN_DEF
    #define PIN_DEF
    #include "pin_definitions.h"
#endif

/**
 * Frequency variable for pwm signal to motor, 3kHz or 4kHz is "100% Speed"
 * Set to 250 as frequency is multiplied by 10 for a 2.5kHz signal
*/
#define motor_pwm_freq 250 
//Duty Cycle variable for pwm signal to motor, duty of 68% is intended
#define motor_pwm_duty 68  

/**
 * @brief turn on/off the PWM signal going to the motor 
 * 
 * @param when true, motor turns on, if false, motor turns off
*/
void motor_on(bool enabled);
