#ifndef LEDS_H
#define LEDS_H

#include <driver/gpio.h>

typedef enum {
    LEDS_GPIO_0 = 0,
    LEDS_GPIO_1,
    LEDS_GPIO_2,
    LEDS_GPIO_3,
    LEDS_GPIO_4,
    LEDS_GPIO_5,
    LEDS_GPIO_6,
    LEDS_GPIO_7,
    LEDS_GPIO_8,
    LEDS_GPIO_9,
    LEDS_GPIO_10,
    LEDS_GPIO_11,
    LEDS_GPIO_12,
    LEDS_GPIO_13,
    LEDS_GPIO_14,
    LEDS_GPIO_15,
    LEDS_GPIO_16,
    LEDS_BUILTIN_RED = LEDS_GPIO_16,
    LEDS_BUILTIN_BLUE = LEDS_GPIO_2
} LEDS_LED_TYPE;

typedef enum {
    LED_ACTIVE_LOW,
    LED_ACTIVE_HIGH
} LED_MODE;

#define LOW_LEVEL 0
#define HIGH_LEVEL 1

#define LED_ON_LEVEL LOW_LEVEL
#define LED_OFF_LEVEL HIGH_LEVEL

void* leds_setup(LEDS_LED_TYPE led_type);
void* leds_setup_mode(LEDS_LED_TYPE led_type, LED_MODE mode);
void leds_cleanup(void* config);
void leds_on(void* config);
void leds_off(void* config);

#endif
