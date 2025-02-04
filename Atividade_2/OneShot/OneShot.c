#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

#define LED_red 13
#define LED_yellow 12
#define LED_green 11
#define BUTTON_a 5
bool led_active = false;
int state = 0;

int64_t turn_on_callback(alarm_id_t id, void *user_data){
    if (state == 0){
        gpio_put(LED_red, 0);
    } else if (state == 1){
        gpio_put(LED_yellow, 0);
    } else if (state == 2){
        gpio_put(LED_green, 0);
    } 

    state++;

    if(state > 2){
        state = 0;
    }
    
}

int main() {
    stdio_init_all();

    gpio_init(LED_red);
    gpio_set_dir(LED_red, GPIO_OUT);

    gpio_init(LED_yellow);
    gpio_set_dir(LED_yellow, GPIO_OUT);

    gpio_init(LED_green);
    gpio_set_dir(LED_green, GPIO_OUT);

    gpio_init(BUTTON_a);
    gpio_set_dir(BUTTON_a, GPIO_IN);
    gpio_pull_up(BUTTON_a);

    struct repeating_timer timer;

    while (true) {
        if(gpio_get(BUTTON_a) == 0 && led_active == false){
            led_active == true;
            int counter = 0;
            gpio_put(LED_red, 1);
            gpio_put(LED_yellow, 1);
            gpio_put(LED_green, 1);
            while (counter < 3){
                printf("Chamou: %d vez(es)\n", counter+1);
                add_alarm_in_ms(3000, turn_on_callback, NULL, false);
                sleep_ms(3000);
                counter++;
            }
            printf("Terminou!\n");

        }

        led_active = false;



       
    }
}
