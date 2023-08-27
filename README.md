# pico_timer_error
Example Project to show an error with the use of the timer in each core of the rp2040

There is one timer running on each core. Each one uses a different alarm pool, which each a initialized with a different hardware alarm.

After Running the project on a pico `assert()` fails:  `assert(rt->alarm_id == id);` in `repeating_timer_callback` in time.c

When yarying the timer intervals (`timer_core_0_delay_us` in main.c and `timer_core_1_delay_us` in second_core.c ) `assert()` does not always fail.




