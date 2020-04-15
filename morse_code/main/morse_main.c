/* Blinky
*/

#include <stdio.h>
#include <stdbool.h>
#include "led.h"
#include "morse.h"


void morse_sos()
{
    char sos[] = "SOS";
    morse_word(sos);
}

void app_main()
{
    printf("Morse SOS!\n");
    led_setup();

    while(true)
    {
        morse_sos();
    }
}
