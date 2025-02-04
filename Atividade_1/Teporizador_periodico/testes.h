#ifndef TESTES_H
#define TESTES_H

#include "pico/types.h"

void run_tests();
void test_gpio_init();
void test_gpio_direction();
void test_repeating_timer_callback();

// Declare a função repeating_timer_callback
bool repeating_timer_callback(struct repeating_timer *t);

#endif // TESTES_H
