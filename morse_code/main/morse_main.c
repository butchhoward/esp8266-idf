/* Blinky
*/

#include <stdio.h>
#include <stdbool.h>
#include "leds.h"
#include "morse.h"
#include "gpio_assistant.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include <driver/gpio.h>


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

#define RELAY_GPIO LEDS_GPIO_12


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


void* relay = 0;
static void relay_on()
{
    leds_on(relay);
}

static void relay_off()
{
    leds_off(relay);
}

static void toggle_relay()
{
    static bool relay_flag = false;

    if (relay_flag)
    {
        relay_on();
    }
    else 
    {
        relay_off();
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

    led_semaphore =  xSemaphoreCreateBinary();
    if (led_semaphore == NULL)
    {
        printf("semaphore creation failed\n");
        return;
    }
    //Semaphore has to be given before it can be taken. Whichever takes first gets it.
    xSemaphoreGive( led_semaphore );

    configure_the_gpio_to_use();

    relay = leds_setup_mode(RELAY_GPIO, LED_ACTIVE_HIGH);
    void* morse_red_config = morse_setup_options( leds_setup(LEDS_BUILTIN_RED), 50);
    void* morse_blue_config = morse_setup_options( leds_setup(LEDS_BUILTIN_BLUE), 100) ;

    xTaskCreate(morse_task, "sos_red", 2048, morse_red_config, 10, NULL);
    xTaskCreate(morse_task, "sos_blue", 2048, morse_blue_config, 10, NULL);

    printf("end of main\n");
}
