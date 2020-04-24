#include "gpio_assistant.h"
#include <stdarg.h>

uint32_t gpio_build_pin_select_mask(int count, ...)
{
    uint32_t mask = 0;

    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; ++i)
    {
        uint32_t pin = va_arg(args, uint32_t);
        mask |= ( 1ULL << pin);
    }
    va_end(args);

    return mask;
}
