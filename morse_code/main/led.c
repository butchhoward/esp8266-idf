#include "led.h"


esp_err_t (*gpio_set_level_impl)(gpio_num_t, uint32_t) = gpio_set_level;
esp_err_t (*gpio_set_direction_impl)(gpio_num_t, gpio_mode_t) = gpio_set_direction;

void led_setup()
{
    gpio_set_direction_impl(LED_BUILTIN, GPIO_MODE_OUTPUT);
    led_off();
}

void led_on()
{
    gpio_set_level_impl(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
                                        // but actually the LED is on; this is because
                                        // it is active low on the ESP-01)
}

void led_off()
{
    gpio_set_level_impl(LED_BUILTIN, HIGH);   // Turn the LED off by making the voltage HIGH
}
