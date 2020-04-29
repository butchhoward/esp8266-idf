#include "relay.h"

#include "internal/relay_priv.h"

void* relay_setup_mode(gpio_num_t io_pin, RELAY_MODE mode)
{
    relay_config_t* config = malloc(sizeof(relay_config_t));

    config->io_pin = io_pin;
    config->mode = mode;

    gpio_set_direction_impl(config->io_pin, GPIO_MODE_OUTPUT);
    relay_off(config);

    return config;
}

void relay_cleanup(void* config)
{
    free(config);
}

extern void (*relay_on)(void* config);
extern void (*relay_off)(void* config);

void (*relay_on)(void*) = relay_on_impl;
void relay_on_impl(void* config)
{
    relay_config_t* c = config;
    uint32_t level = RELAY_LOW_LEVEL;
    if (c->mode == RELAY_ACTIVE_HIGH)
    {
        level = RELAY_HIGH_LEVEL;
    }

    gpio_set_level_impl(c->io_pin, level);
}

void (*relay_off)(void*) = relay_off_impl;
void relay_off_impl(void* config)
{
    relay_config_t* c = config;
    uint32_t level = RELAY_HIGH_LEVEL;
    if (c->mode == RELAY_ACTIVE_HIGH)
    {
        level = RELAY_LOW_LEVEL;
    }
    gpio_set_level_impl(c->io_pin, level);
}

