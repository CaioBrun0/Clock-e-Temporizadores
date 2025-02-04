#ifndef TESTES_H
#define TESTES_H

void run_tests();
void test_gpio_init();
void test_gpio_direction();
void test_turn_on_callback();
void test_button();

int64_t turn_on_callback(alarm_id_t id, void *user_data);

#endif // TESTES_H
