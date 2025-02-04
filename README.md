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
