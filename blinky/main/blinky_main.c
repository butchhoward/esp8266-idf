/* Blinky
*/

#include "led.h"
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


void app_main()
{
    printf("Blinky!\n");
    led_setup();

    while(true)
    {
        led_on();
        vTaskDelay(1000 / portTICK_RATE_MS); // Wait for a second
        led_off();
        vTaskDelay(2000 / portTICK_RATE_MS); // Wait for two seconds (to demonstrate the active low LED)
    }
}
