/* Blinky
*/

#include <stdio.h>
#include <stdbool.h>
#include "leds.h"
#include "morse.h"


void morse_sos(void* morse_config)
{
    char sos[] = "SOS";
    morse_word(morse_config, sos);
}

void app_main()
{
    void* led_config = leds_setup(LEDS_BUILTIN_RED);
    void* morse_config = morse_setup(led_config);

    void* led_blue_config = leds_setup(LEDS_BUILTIN_BLUE);
    void* morse_blue_config = morse_setup(led_blue_config);

    bool use_red=true;

    while(true)
    {
        if (use_red)
        {
            morse_sos(morse_config);
        }
        else
        {
            morse_sos(morse_blue_config);
        }

        use_red = !use_red;
    }

    morse_cleanup(morse_config);
    morse_cleanup(morse_blue_config);
}
