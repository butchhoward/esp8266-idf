#ifndef LED_PRIV_H
#define LED_PRIV_H

#include "led.h"
#include <driver/gpio.h>

#define LED_BUILTIN GPIO_NUM_16
#define LOW_LEVEL 0
#define HIGH_LEVEL 1

#define LED_ON_LEVEL LOW_LEVEL
#define LED_OFF_LEVEL HIGH_LEVEL

extern esp_err_t (*gpio_set_level_impl)(gpio_num_t, uint32_t);
extern esp_err_t (*gpio_set_direction_impl)(gpio_num_t, gpio_mode_t);

void led_on_impl(void);
void led_off_impl(void);

#endif
