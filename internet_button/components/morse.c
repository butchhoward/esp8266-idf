#include "morse.h"
#include "leds.h"
#include <stdio.h>

#include "internal/morse_priv.h"


#define DEFAULT_BASE_TIME 200
#define DOT_TIME 1
#define DASH_TIME 3
#define SYMBOL_SPACE DOT_TIME
#define LETTER_SPACE 3
#define WORD_SPACE 7

typedef enum MORSE_SYMBOL {
    DOT,
    DASH,
    STOP
} MORSE_SYMBOL;

#define MORSE_MAX_SYMBOLS_PER_LETTER 10

typedef struct MORSE_CODE {
    char letter;
    MORSE_SYMBOL code[MORSE_MAX_SYMBOLS_PER_LETTER];
} MORSE_CODE;

MORSE_CODE MORSE_CODES[] = {
     {'A', {DOT,DASH,STOP}}
    ,{'B', {DASH,DOT,DOT,DOT,STOP}}
    ,{'C', {DASH,DOT,DASH,DOT,STOP}}
    ,{'D', {DASH,DOT,DOT,STOP}}
    ,{'E', {DOT,STOP}}
    ,{'F', {DOT,DOT,DASH,DOT,STOP}}
    ,{'G', {DASH,DASH,DOT,STOP}}
    ,{'H', {DOT,DOT,DOT,DOT,STOP}}
    ,{'I', {DOT,DOT,STOP}}
    ,{'J', {DOT,DASH,DASH,DASH,STOP}}
    ,{'K', {DASH,DOT,DASH,STOP}}
    ,{'L', {DOT,DASH,DOT,DOT,STOP}}
    ,{'M', {DASH,DASH,STOP}}
    ,{'N', {DASH,DOT,STOP}}
    ,{'O', {DASH,DASH,DASH,STOP}}
    ,{'P', {DOT,DASH,DASH,DOT,STOP}}
    ,{'Q', {DASH,DASH,DOT,DASH,STOP}}
    ,{'R', {DOT,DASH,DOT,STOP}}
    ,{'S', {DOT,DOT,DOT,STOP}}
    ,{'T', {DASH,STOP}}
    ,{'U', {DOT,DOT,DASH,STOP}}
    ,{'V', {DOT,DOT,DOT,DASH,STOP}}
    ,{'W', {DOT,DASH,DASH,STOP}}
    ,{'X', {DASH,DOT,DOT,DASH,STOP}}
    ,{'Y', {DASH,DOT,DASH,DASH,STOP}}
    ,{'Z', {DASH,DASH,DOT,DOT,STOP}}
    ,{'0', {DASH,DASH,DASH,DASH,DASH,STOP}}
    ,{'1', {DOT,DASH,DASH,DASH,DASH,STOP}}
    ,{'2', {DOT,DOT,DASH,DASH,DASH,STOP}}
    ,{'3', {DOT,DOT,DOT,DASH,DASH,STOP}}
    ,{'4', {DOT,DOT,DOT,DOT,DASH,STOP}}
    ,{'5', {DOT,DOT,DOT,DOT,DOT,STOP}}
    ,{'6', {DASH,DOT,DOT,DOT,DOT,STOP}}
    ,{'7', {DASH,DASH,DOT,DOT,DOT,STOP}}
    ,{'8', {DASH,DASH,DASH,DOT,DOT,STOP}}
    ,{'9', {DASH,DASH,DASH,DASH,DOT,STOP}}
    ,{'.', {DOT,DASH,DOT,DASH,DOT,DASH,STOP}}
    ,{',', {DASH,DASH,DOT,DOT,DASH,DASH,STOP}}
    ,{'?', {DOT,DOT,DASH,DASH,DOT,DOT,STOP}}
    ,{'\'',{DOT,DASH,DASH,DASH,DASH,DOT,STOP}}
    ,{'!', {DASH,DOT,DASH,DOT,DASH,DASH,STOP}}
    ,{'/', {DASH,DOT,DOT,DASH,DOT,STOP}}
    ,{'(', {DASH,DOT,DASH,DASH,DOT,STOP}}
    ,{')', {DASH,DOT,DASH,DASH,DOT,DASH,STOP}}
    ,{'&', {DOT,DASH,DOT,DOT,DOT,STOP}}
    ,{':', {DASH,DASH,DASH,DOT,DOT,DOT,STOP}}
    ,{';', {DASH,DOT,DASH,DOT,DASH,DOT,STOP}}
    ,{'=', {DASH,DOT,DOT,DOT,DASH,STOP}}
    ,{'+', {DOT,DASH,DOT,DASH,DOT,STOP}}
    ,{'-', {DASH,DOT,DOT,DOT,DOT,DASH,STOP}}
    ,{'_', {DOT,DOT,DASH,DASH,DOT,DASH,STOP}}
    ,{'"', {DOT,DASH,DOT,DOT,DASH,DOT,STOP}}
    ,{'$', {DOT,DOT,DOT,DASH,DOT,DOT,DASH,STOP}}
    ,{'@', {DOT,DASH,DASH,DOT,DASH,DOT,STOP}}

    ,{'\0', {STOP}}
};

void* morse_setup(void* led_config)
{
    return morse_setup_options(led_config, DEFAULT_BASE_TIME);
}

void* morse_setup_options(void* led_config, unsigned int base_time)
{
    morse_config_t* config = malloc(sizeof(morse_config_t));
    config->led_config = led_config;
    config->base_time = base_time;

    return config;
}

void morse_cleanup(void* morse_config)
{
    morse_config_t* c = morse_config;
    free(c->led_config);
    free(c);
}

void (*morse_dot_delay)(void* morse_config) = morse_dot_delay_impl;
void morse_dot_delay_impl(void* morse_config)
{
    morse_config_t* c = (morse_config_t*)morse_config;
    vTaskDelay_impl( (c->base_time * DOT_TIME) / portTICK_RATE_MS);
}

void (*morse_dash_delay)(void* morse_config) = morse_dash_delay_impl;
void morse_dash_delay_impl(void* morse_config)
{
    morse_config_t* c = (morse_config_t*)morse_config;
    vTaskDelay_impl((c->base_time * DASH_TIME) / portTICK_RATE_MS);
}

void morse_symbol_delay(void* morse_config)
{
    morse_config_t* c = (morse_config_t*)morse_config;
    vTaskDelay_impl((c->base_time * SYMBOL_SPACE) / portTICK_RATE_MS);
}

void morse_letter_delay(void* morse_config)
{
    morse_config_t* c = (morse_config_t*)morse_config;
    vTaskDelay_impl((c->base_time * LETTER_SPACE) / portTICK_RATE_MS);
}

void morse_word_delay(void* morse_config)
{
    morse_config_t* c = (morse_config_t*)morse_config;
    vTaskDelay_impl((c->base_time * WORD_SPACE) / portTICK_RATE_MS);
}

void (*morse_dot)(void*) = morse_dot_impl;
void morse_dot_impl(void* morse_config)
{
    morse_config_t* c = (morse_config_t*)morse_config;

    leds_on(c->led_config);
    morse_dot_delay(morse_config);
    leds_off(c->led_config);
}

void (*morse_dash)(void*) = morse_dash_impl;
void morse_dash_impl(void* morse_config)
{
    morse_config_t* c = (morse_config_t*)morse_config;
    leds_on(c->led_config);
    morse_dash_delay(morse_config);
    leds_off(c->led_config);
}

void morse_letter_symbols(void* morse_config, const MORSE_SYMBOL* symbols)
{
    for (;*symbols != STOP; symbols++)
    {
        if (*symbols == DOT)
        {
            morse_dot(morse_config);
        }
        else 
        {
            morse_dash(morse_config);
        }
        morse_symbol_delay(morse_config);
    }
}

void (*morse_letter)(void* morse_config, const char c) = morse_letter_impl;
void morse_letter_impl(void* morse_config, const char c)
{
    MORSE_CODE* S = &MORSE_CODES[0];
    for (; S->letter != '\0'; S++)
    {
        if ( c == S->letter)
        {
            break;
        }
    }
    if (S->letter != '\0')
    {
        morse_letter_symbols(morse_config, S->code );
        morse_letter_delay(morse_config);
    }
}

void morse_word(void* morse_config, const char* word)
{

    for (; *word; word++)
    {
        morse_letter(morse_config, *word);
    }
    morse_word_delay(morse_config);

}
