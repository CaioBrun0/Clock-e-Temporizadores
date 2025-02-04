# Clock e Temporizadores

Este repositório contém dois projetos de atividades que envolvem o uso de temporizadores e LEDs na plataforma Raspberry Pi Pico.

## Atividade 1: Temporizador Periódico

Este projeto utiliza um temporizador periódico para alternar entre três LEDs (vermelho, amarelo e verde) a cada 3 segundos.

### Código

```c
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "testes.h"

// Define as constantes
#define LED_red 13
#define LED_yellow 12
#define LED_green 11

// Guarda o estado
int state = 0;

// Função de callback
bool repeating_timer_callback(struct repeating_timer *t) {
    // Inicia com todos desligados e, dependendo da variável state, acende o próximo LED
    gpio_put(LED_red, 0);
    gpio_put(LED_yellow, 0);
    gpio_put(LED_green, 0);

    if (state == 0) {
        gpio_put(LED_red, 1);
    } else if (state == 1) {
        gpio_put(LED_yellow, 1);
    } else if (state == 2) {
        gpio_put(LED_green, 1);
    }

    // Atualiza o valor do estado
    if (state == 2) {
        state = 0;
    } else {
        state++;
    }
        
    return true;    
}

int main() {
    stdio_init_all();

    // Execute os testes
    run_tests();

    // Inicializa os pinos e chama a função de callback a cada 3 segundos
    gpio_init(LED_red);
    gpio_set_dir(LED_red, GPIO_OUT);

    gpio_init(LED_yellow);
    gpio_set_dir(LED_yellow, GPIO_OUT);

    gpio_init(LED_green);
    gpio_set_dir(LED_green, GPIO_OUT);

    struct repeating_timer timer;

    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    while (true) {
        sleep_ms(1000);
        printf("Passou 1 segundo\n");
    }
}

# Atividade 2: Temporizador com Botão

Este projeto utiliza um temporizador e um botão para controlar três LEDs (vermelho, azul e verde). Os LEDs são ativados quando o botão é pressionado, e o temporizador apaga cada LED sequencialmente a cada 3 segundos.

## Código

```c
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "testes.h"

// Declaração das constantes
#define LED_red 13
#define LED_blue 12
#define LED_green 11
#define BUTTON_a 5

// Variável booleana para saber se o led está aceso
bool led_active = false;

// Guarda o estado
int state = 0;

// Função do temporizador
int64_t turn_on_callback(alarm_id_t id, void *user_data) {
    // Apaga um LED dependendo do valor da variável state
    if (state == 0) {
        gpio_put(LED_blue, 0);
    } else if (state == 1) {
        gpio_put(LED_red, 0);
    } else if (state == 2) {
        gpio_put(LED_green, 0);
    } 

    // Incrementa mais 1 na variável state. Se passar de 2, o valor volta para 0
    state++;
    if (state > 2) {
        state = 0;
    }
}

int main() {
    stdio_init_all();

    // Executa todos os testes
    run_tests();

    // Inicializa os LEDs e o botão
    gpio_init(LED_red);
    gpio_set_dir(LED_red, GPIO_OUT);

    gpio_init(LED_blue);
    gpio_set_dir(LED_blue, GPIO_OUT);

    gpio_init(LED_green);
    gpio_set_dir(LED_green, GPIO_OUT);

    gpio_init(BUTTON_a);
    gpio_set_dir(BUTTON_a, GPIO_IN);
    gpio_pull_up(BUTTON_a);

    struct repeating_timer timer;

    while (true) {
        // Verifica se o botão foi pressionado e se os LEDs estão ativos
        if (gpio_get(BUTTON_a) == 0 && led_active == false) {
            led_active = true;
            gpio_put(LED_blue, 1);
            gpio_put(LED_red, 1);
            gpio_put(LED_green, 1);

            int counter = 0;
            while (counter < 3) {
                add_alarm_in_ms(3000, turn_on_callback, NULL, false);
                sleep_ms(3000);
                counter++;
            }
        }
        led_active = false;
    }
}
