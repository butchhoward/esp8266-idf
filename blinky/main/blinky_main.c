/* Blinky
*/

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED_BUILTIN GPIO_NUM_16
#define LOW 0
#define HIGH 1

void app_main()
{
    printf("Blinky!\n");

    gpio_set_direction(LED_BUILTIN, GPIO_MODE_OUTPUT);

    while(true)
    {
        gpio_set_level(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
                                            // but actually the LED is on; this is because
                                            // it is active low on the ESP-01)
        vTaskDelay(1000 / portTICK_RATE_MS); // Wait for a second
        gpio_set_level(LED_BUILTIN, HIGH);   // Turn the LED off by making the voltage HIGH
        vTaskDelay(2000 / portTICK_RATE_MS); // Wait for two seconds (to demonstrate the active low LED)
    }
}
