#include "led.h"
#include <driver/gpio.h>

#define LED_BUILTIN GPIO_NUM_16
#define LOW 0
#define HIGH 1

void led_setup()
{
    gpio_set_direction(LED_BUILTIN, GPIO_MODE_OUTPUT);
    gpio_set_level(LED_BUILTIN, HIGH);   // Turn the LED off by making the voltage HIGH
}

void led_on()
{
    gpio_set_level(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
                                        // but actually the LED is on; this is because
                                        // it is active low on the ESP-01)
}

void led_off()
{
    gpio_set_level(LED_BUILTIN, HIGH);   // Turn the LED off by making the voltage HIGH
}
