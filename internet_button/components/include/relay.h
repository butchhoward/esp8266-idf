#ifndef RELAY_H
#define RELAY_H

#include <driver/gpio.h>


#define RELAY_LOW_LEVEL 0
#define RELAY_HIGH_LEVEL 1

typedef enum {
    RELAY_ACTIVE_LOW,
    RELAY_ACTIVE_HIGH
} RELAY_MODE;


void* relay_setup_mode(gpio_num_t io_pin, RELAY_MODE mode);
void relay_cleanup(void* config);
extern void (*relay_on)(void* config);
extern void (*relay_off)(void* config);

#endif
