#ifndef LED_H
#define LED_H

#include <driver/gpio.h>

#define LED_BUILTIN GPIO_NUM_16
#define LOW 0
#define HIGH 1

extern esp_err_t (*gpio_set_level_impl)(gpio_num_t, uint32_t);
extern esp_err_t (*gpio_set_direction_impl)(gpio_num_t, gpio_mode_t);

extern void (*led_on)(void);
void led_on_impl(void);

extern void (*led_off)(void);
void led_off_impl(void);

void led_setup();

#endif
