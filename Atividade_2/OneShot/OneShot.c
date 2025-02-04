#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "testes.h"

//Declaração das constantes
#define LED_red 13
#define LED_blue 12
#define LED_green 11
#define BUTTON_a 5
//Variavel booleane para saber se o led está acesso
bool led_active = false;
//Guarda o estado
int state = 0;

//Função do temporizador
int64_t turn_off_callback(alarm_id_t id, void *user_data){
    //Apaga um LED dependendo do valor da variavel state
    if (state == 0){
        gpio_put(LED_blue, 0);
    } else if (state == 1){
        gpio_put(LED_red, 0);
    } else if (state == 2){
        gpio_put(LED_green, 0);
    } 

    //Incrementa mais 1 na variavel state, se passar de 2, o valor volta para 0
    state++;
    if(state > 2){
        state = 0;
    }
    
}

int main() {
    stdio_init_all();

    // Executa todos os testes
    run_tests();

    //inicializa os LEDS e o botão
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
        //Verifica se o botão foi pressionado e se os LEDS estão ativos
        if(gpio_get(BUTTON_a) == 0 && led_active == false){
            led_active = true;
            gpio_put(LED_blue, 1);
            gpio_put(LED_red, 1);
            gpio_put(LED_green, 1);

            int counter = 0;
            while (counter < 3){
                add_alarm_in_ms(3000, turn_off_callback, NULL, false);
                sleep_ms(3000);
                counter++;
            }
        }
        led_active = false;

    }
}
