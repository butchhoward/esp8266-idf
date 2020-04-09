#include "driver/gpio.h"


esp_err_t gpio_set_level(gpio_num_t gpio_num, uint32_t level)
{
    return ESP_OK;
}

esp_err_t gpio_set_direction(gpio_num_t gpio_num, gpio_mode_t mode)
{
    return ESP_OK;
}

void gpio_pad_select_gpio(uint8_t gpio_num)
{
    // Do Nothing
}
