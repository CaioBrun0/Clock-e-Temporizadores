#include <assert.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"
#include "testes.h"

#define LED_red 13
#define LED_yellow 12
#define LED_green 11
extern int state;

//Verifica se os pinos foram inicializados
void test_gpio_init() {
    assert(gpio_is_initialized(LED_red));
    assert(gpio_is_initialized(LED_yellow));
    assert(gpio_is_initialized(LED_green));
}

//Verifica se os pinos estão na direção correta (saída)
void test_gpio_direction() {
    assert(gpio_get_dir(LED_red) == GPIO_OUT);
    assert(gpio_get_dir(LED_yellow) == GPIO_OUT);
    assert(gpio_get_dir(LED_green) == GPIO_OUT);
}

//Testa a função de callback e muda o valor do LED dependendo da variavél state
void test_repeating_timer_callback() {
    state = 0;
    repeating_timer_callback(NULL);
    assert(gpio_get(LED_red) == 1);
    assert(gpio_get(LED_yellow) == 0);
    assert(gpio_get(LED_green) == 0);

    state = 1;
    repeating_timer_callback(NULL);
    assert(gpio_get(LED_red) == 0);
    assert(gpio_get(LED_yellow) == 1);
    assert(gpio_get(LED_green) == 0);

    state = 2;
    repeating_timer_callback(NULL);
    assert(gpio_get(LED_red) == 0);
    assert(gpio_get(LED_yellow) == 0);
    assert(gpio_get(LED_green) == 1);
}

//Roda todos os testes
void run_tests() {
    test_gpio_init();
    test_gpio_direction();
    test_repeating_timer_callback();
    printf("Todos os testes passaram!\n");
}
