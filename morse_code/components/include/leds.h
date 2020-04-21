#ifndef LEDS_H
#define LEDS_H

#include <driver/gpio.h>

typedef enum {
    LEDS_GPIO_0 = GPIO_NUM_0,
    LEDS_GPIO_1 = GPIO_NUM_1,
    LEDS_GPIO_2 = GPIO_NUM_2,
    LEDS_GPIO_3 = GPIO_NUM_3,
    LEDS_GPIO_4 = GPIO_NUM_4,
    LEDS_GPIO_5 = GPIO_NUM_5,
    LEDS_GPIO_6 = GPIO_NUM_6,
    LEDS_GPIO_7 = GPIO_NUM_7,
    LEDS_GPIO_8 = GPIO_NUM_8,
    LEDS_GPIO_9 = GPIO_NUM_9,
    LEDS_GPIO_10 = GPIO_NUM_10,
    LEDS_GPIO_11 = GPIO_NUM_11,
    LEDS_GPIO_12 = GPIO_NUM_12,
    LEDS_GPIO_13 = GPIO_NUM_13,
    LEDS_GPIO_14 = GPIO_NUM_14,
    LEDS_GPIO_15 = GPIO_NUM_15,
    LEDS_GPIO_16 = GPIO_NUM_16
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
extern void (*leds_on)(void* config);
extern void (*leds_off)(void* config);

#endif
