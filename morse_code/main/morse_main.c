/* Blinky
*/

#include <stdio.h>
#include <stdbool.h>
#include "leds.h"
#include "morse.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


static void morse_task(void *morse_config)
{
    char sos[] = "SOS";
    for (;;)
    {
        morse_word(morse_config, sos);
    }
}


void app_main()
{
    void* led_red_config = leds_setup(LEDS_BUILTIN_RED);
    void* morse_red_config = morse_setup(led_red_config);

    void* led_blue_config = leds_setup(LEDS_BUILTIN_BLUE);
    void* morse_blue_config = morse_setup(led_blue_config);

    xTaskCreate(morse_task, "sos_red", 2048, morse_red_config, 10, NULL);
    xTaskCreate(morse_task, "sos_blue", 2048, morse_blue_config, 10, NULL);

    morse_cleanup(morse_blue_config);
    morse_cleanup(morse_red_config);
}
