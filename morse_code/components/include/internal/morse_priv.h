#ifndef MORSE_PRIV_H
#define MORSE_PRIV_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "indirections.h"


#define DOT_TIME 200
#define DASH_TIME (DOT_TIME * 3)
#define SYMBOL_SPACE DOT_TIME
#define LETTER_SPACE (DOT_TIME * 3)
#define WORD_SPACE (DOT_TIME * 7)

extern void (*morse_dot)(void);
void morse_dot_impl();

extern void (*morse_dash)(void);
void morse_dash_impl();

extern void (*morse_dot_delay)(void);
void morse_dot_delay_impl();

extern void (*morse_dash_delay)(void);
void morse_dash_delay_impl();

void morse_letter_impl(const char c);



#endif
