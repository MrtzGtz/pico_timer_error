#include "second_core.h"

#include "pico/time.h"
#include "pico/platform.h"
#include "hardware/irq.h"

uint core_1_hw_alarm = TIMER_IRQ_2; // use a different than core 0
int64_t timer_core_1_delay_us = 60;

alarm_pool_t* alarm_pool_core_1;
int max_timers_core_1 = 1;
repeating_timer_t timer_core_1;
volatile bool core_1_in_timer_cb = false;

bool timer_callback_core_1(repeating_timer_t *rt);

void second_core_entry() 
{
    alarm_pool_core_1 = alarm_pool_create(core_1_hw_alarm, max_timers_core_1);
    
    alarm_pool_add_repeating_timer_us(alarm_pool_core_1,
        -timer_core_1_delay_us,
        timer_callback_core_1,
        NULL,
        &timer_core_1);

    while(1)
    {
        tight_loop_contents();
    }
}

volatile int timer_core1_cb_count = 0;

bool timer_callback_core_1(repeating_timer_t *rt)
{    
    timer_core1_cb_count++;
    
    return true;
}
