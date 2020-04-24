/* Internet Button
*/

#include <stdio.h>
#include <stdbool.h>
#include "leds.h"
#include "relay.h"
#include "morse.h"
#include "gpio_assistant.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include <driver/gpio.h>


SemaphoreHandle_t led_semaphore = NULL;
void configure_the_semaphore()
{
    led_semaphore =  xSemaphoreCreateBinary();
    if (led_semaphore == NULL)
    {
        printf("semaphore creation failed\n");
        return;
    }
    //Semaphore has to be given before it can be taken. Whichever takes first gets it.
    xSemaphoreGive( led_semaphore );
}


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

#define RELAY_GPIO GPIO_NUM_12


void configure_the_gpio_to_use()
{
    //must configure IO before using it (the built in leds worked by accident)
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = gpio_build_pin_select_mask(3, RELAY_GPIO, LEDS_BUILTIN_RED, LEDS_BUILTIN_BLUE);
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    if (gpio_config(&io_conf) != ESP_OK)
    {
        printf("gpio_config failed\n");
    }
}


void* relay_config = 0;

static void toggle_relay()
{
    static bool relay_flag = false;

    if (relay_flag)
    {
        relay_on(relay_config);
    }
    else 
    {
        relay_off(relay_config);
    }
    relay_flag = !relay_flag;
}

static void morse_task(void *morse_config)
{
    char sos[] = "SOS";
    for (;;)
    {
        //wait (possibly forever) for the semaphore to become available
        xSemaphoreTake( led_semaphore, portMAX_DELAY );
        toggle_relay();
        morse_word(morse_config, sos);
        xSemaphoreGive( led_semaphore );

        //must yield/delay in some way to give the task manager time to go to another task
        taskYIELD();
    }
}



void app_main()
{
    printf("start of main\n");

    configure_the_semaphore();
    configure_the_gpio_to_use();

    relay_config = relay_setup_mode(RELAY_GPIO, RELAY_ACTIVE_HIGH);
    void* morse_red_config = morse_setup_options( leds_setup(LEDS_BUILTIN_RED), 50);
    void* morse_blue_config = morse_setup_options( leds_setup(LEDS_BUILTIN_BLUE), 100) ;

    xTaskCreate(morse_task, "sos_red", 2048, morse_red_config, 10, NULL);
    xTaskCreate(morse_task, "sos_blue", 2048, morse_blue_config, 10, NULL);

    printf("end of main\n");
}
