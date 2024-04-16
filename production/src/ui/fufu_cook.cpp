#include "fufu_cook.h"

void cook(cooking_type firmness) {
    /**
     *  define cooking variable and set times for regular cycle as default, times are in seconds
    */
    uint8_t pump_time_1;
    uint8_t pump_time_2;
    uint8_t pump_time_3;
    uint8_t motor_time_1;
    uint8_t motor_time_2;
    uint8_t motor_time_3;

    //sets timing variables for each case, default case is for regular firmness
    switch (firmness)
    {
    case firm:
        pump_time_1 = 120;
        pump_time_2 = 80;
        pump_time_3 = 80;
        motor_time_1 = 600;
        motor_time_2 = 300;
        motor_time_3 = 300;
        break;
    case soft:
        pump_time_1 = 180;
        pump_time_2 = 120;
        pump_time_3 = 120;
        motor_time_1 = 600;
        motor_time_2 = 300;
        break;

    default:
        pump_time_1 = 150;
        pump_time_2 = 100;
        pump_time_3 = 100;
        motor_time_1 = 600;
        motor_time_2 = 300;
        break;
    }

    //turns on water pump and pumps for an amount of time set above
    pump_water(true);
    for (int i = 0; i < pump_time_1; i++) {
        if(!is_water_not_empty()) {
            pump_water(false);
            return;
        }
        Sleep(1000);
    }
    //pump off
    pump_water(false);

    //turn on heat and motor for second mixing step
    heat_on(true);
    motor_on(true);
    for (int i = 0; i < motor_time_1; i++) {
        Sleep(1000);
    }

    //motor off, leave heat on for next step
    motor_on(false);

    //second pumping step
    pump_water(true);
    for (int i = 0; i < pump_time_2; i++) {
        if(!is_water_not_empty()) {
            pump_water(false);
            return;
        }
        Sleep(1000);
    }
    pump_water(false);

    //second motor step
    motor_on(true);
    for (int i = 0; i < motor_time_2; i++) {
        Sleep(1000);
    }
    //turn off motor but leave heat on
    motor_on(false);

    //third pumping step
    pump_water(true);
    for (int i = 0; i < pump_time_3; i++) {
        if(!is_water_not_empty()) {
            pump_water(false);
            return;
        }
        Sleep(1000);
    }
    //turn off pump, heat still on
    pump_water(false);

    //third motor step
    motor_on(true);
    for (int i = 0; i < motor_time_3; i++) {
        Sleep(1000);
    }
    //turn off motor but leave heat on
    motor_on(false);

    //turn heat off at the end
    heat_on(false);
}

void soft_cook() {
    
}

void reg_cook() {

}

void firm_cook() {
    
}