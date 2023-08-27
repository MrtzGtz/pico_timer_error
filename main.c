#include "pico/time.h"
#include "pico/multicore.h"
#include "pico/platform.h"

#include "hardware/irq.h"

#include "second_core.h"
#include <assert.h>

uint core_0_hw_alarm = TIMER_IRQ_1;
const int64_t timer_core_0_delay_us = 40;

alarm_pool_t* alarm_pool_core_0;
int max_timers_core_0 = 1;
repeating_timer_t timer_core_0;
uint64_t timer_start_us = 0;

bool timer_callback_core_0(repeating_timer_t *rt);

int main()
{
    multicore_launch_core1(second_core_entry);

    alarm_pool_core_0 = alarm_pool_create(core_0_hw_alarm, max_timers_core_0);
    
    timer_start_us = time_us_64();
    alarm_pool_add_repeating_timer_us(alarm_pool_core_0,
        -timer_core_0_delay_us,
        timer_callback_core_0,
        NULL,
        &timer_core_0);
    while(1)
    {
        tight_loop_contents();
    }
}

volatile int timer_core0_cb_count = 0;

bool timer_callback_core_0(repeating_timer_t *rt)
{
    timer_core0_cb_count++;
    return true;
}
