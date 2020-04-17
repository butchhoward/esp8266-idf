#ifndef MORSE_H
#define MORSE_H

void* morse_setup(void* led_config);
void morse_cleanup(void* morse_config);

extern void (*morse_letter)(const char c);
void morse_word(const char* word);

#endif
