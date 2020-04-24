#ifndef relay_PRIV_H
#define relay_PRIV_H

#include "relay.h"
#include "indirections.h"


typedef struct relay_config_t 
{
    gpio_num_t io_pin;
    RELAY_MODE mode;
} relay_config_t;


void relay_on_impl(void*);
void relay_off_impl(void*);

#endif
