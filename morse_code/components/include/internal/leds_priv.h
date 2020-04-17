#ifndef LEDS_PRIV_H
#define LEDS_PRIV_H

#include "leds.h"
#include "indirections.h"


typedef struct leds_config_t 
{
    LEDS_LED_TYPE led_type;
    LED_MODE mode;
} leds_config_t;

#endif
