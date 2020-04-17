#include "led.h"
#include "internal/led_priv.h"

void led_setup()
{
    gpio_set_direction_impl(LED_BUILTIN, GPIO_MODE_OUTPUT);
    led_off();
}

void (*led_on)(void) = led_on_impl;
void led_on_impl()
{
    gpio_set_level_impl(LED_BUILTIN, LED_ON_LEVEL);
}

void (*led_off)(void) = led_off_impl;
void led_off_impl()
{
    gpio_set_level_impl(LED_BUILTIN, LED_OFF_LEVEL);   // Turn the LED off by making the voltage HIGH
}
