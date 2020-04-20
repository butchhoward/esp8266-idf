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
    printf("start of main\n");
    void* led_red_config = leds_setup(LEDS_BUILTIN_RED);
    void* morse_red_config = morse_setup(led_red_config);

    void* led_blue_config = leds_setup(LEDS_BUILTIN_BLUE);
    void* morse_blue_config = morse_setup(led_blue_config);

    xTaskCreate(morse_task, "sos_red", 2048, morse_red_config, 10, NULL);
    xTaskCreate(morse_task, "sos_blue", 2048, morse_blue_config, 10, NULL);

    //the actual entry point of the program is defined in the linker scripts as call_start_cpu()
    //call_start_cpu() creates a task with the function user_init_entry() and starts the task scheduler
    //user_init_entry() does some things, calls app_main(), then calls vTaskDelete after main exits causing its task to be deleted
    //the task scheduler is still running and will execute any other task that were created
    
    //since our morse_config objects are alocated from the heap, they are still valid unless we foolishly delete them here
    //  (in which case, the task will probably continue to work because the memory is likely not scrubbed.)

    //I put the scope on this version to see how close the leds were in timing.  The red led (first task added)
    //fires the led about 20us before the blue led.

    printf("end of main\n");
}
