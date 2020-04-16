#ifndef LED_H
#define LED_H

void led_setup();
extern void (*led_on)(void);
extern void (*led_off)(void);

#endif
