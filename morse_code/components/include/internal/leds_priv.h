#ifndef LEDS_PRIV_H
#define LEDS_PRIV_H

#include "leds.h"

extern esp_err_t (*gpio_set_level_impl)(gpio_num_t, uint32_t);
extern esp_err_t (*gpio_set_direction_impl)(gpio_num_t, gpio_mode_t);

typedef struct leds_config_t 
{
    LEDS_LED_TYPE led_type;
    LED_MODE mode;
} leds_config_t;

#endif
