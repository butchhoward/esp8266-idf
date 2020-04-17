#include <driver/gpio.h>

//stubs to stand in for the real things for the test builds
esp_err_t (*gpio_set_level_impl)(gpio_num_t, uint32_t) = gpio_set_level;
esp_err_t (*gpio_set_direction_impl)(gpio_num_t, gpio_mode_t) = gpio_set_direction;

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
