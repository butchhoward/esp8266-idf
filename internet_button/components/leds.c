#include "leds.h"
#include "internal/leds_priv.h"

#include <stdlib.h>

void* leds_setup(LEDS_LED_TYPE led_type)
{
    return leds_setup_mode(led_type, LED_ACTIVE_LOW);
}

void* leds_setup_mode(LEDS_LED_TYPE led_type, LED_MODE mode)
{
    leds_config_t* config = malloc(sizeof(leds_config_t));

    config->led_type = led_type;
    config->mode = mode;

    gpio_set_direction_impl( (gpio_num_t)config->led_type, GPIO_MODE_OUTPUT);
    leds_off(config);

    return config;
}

void leds_cleanup(void* config)
{
    free(config);
}

void (*leds_on)(void*) = leds_on_impl;
void leds_on_impl(void* config)
{
    leds_config_t* c = config;
    uint32_t level = LOW_LEVEL;
    if (c->mode == LED_ACTIVE_HIGH)
    {
        level = HIGH_LEVEL;
    }

    gpio_set_level_impl((gpio_num_t)c->led_type, level);
}

void (*leds_off)(void*) = leds_off_impl;
void leds_off_impl(void* config)
{
    leds_config_t* c = config;
    uint32_t level = HIGH_LEVEL;
    if (c->mode == LED_ACTIVE_HIGH)
    {
        level = LOW_LEVEL;
    }
    gpio_set_level_impl((gpio_num_t)c->led_type, level);
}
