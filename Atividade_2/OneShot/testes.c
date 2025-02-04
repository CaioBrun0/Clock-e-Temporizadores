#include <assert.h>
#include "pico/stdlib.h"
#include <stdio.h> 
#include "hardware/gpio.h"
#include "testes.h"

#define LED_red 13
#define LED_blue 12
#define LED_green 11
#define BUTTON_a 5
extern int state;

//Verifica se os pinos estão configurados corretamente
void test_gpio_init() {
    assert(gpio_is_initialized(LED_red));
    assert(gpio_is_initialized(LED_blue));
    assert(gpio_is_initialized(LED_green));
    assert(gpio_is_initialized(BUTTON_a));
}

//Verifica se os pinos tem direção correta (entrada e saida)
void test_gpio_direction() {
    assert(gpio_get_dir(LED_red) == GPIO_OUT);
    assert(gpio_get_dir(LED_blue) == GPIO_OUT);
    assert(gpio_get_dir(LED_green) == GPIO_OUT);
    assert(gpio_get_dir(BUTTON_a) == GPIO_IN);
}

//Verifica se a função de callback do alarme está funcionando corretamente
void test_turn_on_callback() {
    state = 0;
    turn_on_callback(0, NULL);
    assert(gpio_get(LED_red) == 0);

    state = 1;
    turn_on_callback(0, NULL);
    assert(gpio_get(LED_blue) == 0);

    state = 2;
    turn_on_callback(0, NULL);
    assert(gpio_get(LED_green) == 0);
}

// Simula o pressionamento do botão
void test_button() {
    gpio_put(BUTTON_a, 0); 
    assert(gpio_get(BUTTON_a) == 0);
}

//Chama todos os testes e avisa se todos os testes passaram
void run_tests() {
    test_gpio_init();
    test_gpio_direction();
    test_turn_on_callback();
    test_button();
    printf("Todos os testes passaram!\n");
}
