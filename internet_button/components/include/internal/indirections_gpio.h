#ifndef INDIRECTIONS_GPIO_H
#define INDIRECTIONS_GPIO_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include <driver/gpio.h>

extern esp_err_t (*gpio_set_level_impl)(gpio_num_t, uint32_t);
extern esp_err_t (*gpio_set_direction_impl)(gpio_num_t, gpio_mode_t);

extern void (*vTaskDelay_impl)(const TickType_t xTicksToDelay);

#endif
