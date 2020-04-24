
#include "internal/indirections.h"

esp_err_t (*gpio_set_level_impl)(gpio_num_t, uint32_t) = gpio_set_level;
esp_err_t (*gpio_set_direction_impl)(gpio_num_t, gpio_mode_t) = gpio_set_direction;

void (*vTaskDelay_impl)(const TickType_t xTicksToDelay) = vTaskDelay;
