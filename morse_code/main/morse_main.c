/* Blinky
*/

#include <stdio.h>
#include <stdbool.h>
#include "leds.h"
#include "morse.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

SemaphoreHandle_t led_semaphore = NULL;

#define DEVICE_TYPE_FEATHER
// #define DEVICE_TYPE_WAVESHARE

#if defined(DEVICE_TYPE_WAVESHARE)
    #define LEDS_BUILTIN_RED LEDS_GPIO_16
    #define LEDS_BUILTIN_BLUE LEDS_GPIO_2
#elif defined(DEVICE_TYPE_FEATHER)
    #define LEDS_BUILTIN_RED LEDS_GPIO_0
    #define LEDS_BUILTIN_BLUE LEDS_GPIO_2
#else
    #error "Use a known DEVICE_TYPE_XXX"
#endif


static void morse_task(void *morse_config)
{
    char sos[] = "SOS";
    for (;;)
    {
        //wait (possibly forever) for the semaphore to become available
        xSemaphoreTake( led_semaphore, portMAX_DELAY );
        morse_word(morse_config, sos);
        xSemaphoreGive( led_semaphore );

        //must yield/delay in some way to give the task manager time to go to another task
        taskYIELD();
    }
}


void app_main()
{
    printf("start of main\n");

    led_semaphore =  xSemaphoreCreateBinary();
    if (led_semaphore == NULL)
    {
        printf("semaphore creation failed\n");
        return;
    }
    //Semaphore has to be given before it can be taken. Whichever takes first gets it.
    xSemaphoreGive( led_semaphore );


    void* led_red_config = leds_setup(LEDS_GPIO_0);
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

    //Using a semaphore to let each color task complete its message without the other flashing.

    printf("end of main\n");
}
