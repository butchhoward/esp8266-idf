#ifndef MORSE_PRIV_H
#define MORSE_PRIV_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "indirections.h"


typedef struct morse_config_t 
{
    void* led_config;
    unsigned int base_time;
} morse_config_t;


extern void (*morse_dot)(void*);
void morse_dot_impl(void*);

extern void (*morse_dash)(void*);
void morse_dash_impl(void*);

extern void (*morse_dot_delay)(void*);
void morse_dot_delay_impl(void*);

extern void (*morse_dash_delay)(void*);
void morse_dash_delay_impl(void*);

void morse_letter_impl(void*, const char c);



#endif
