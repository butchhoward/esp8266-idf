#include "unity_fixture.h"
#include <stdbool.h>
#include "gpio_assistant.h"
#include <driver/gpio.h>

#include "fff.h"

DEFINE_FFF_GLOBALS;

TEST_GROUP(gpio_assistant);

TEST_SETUP(gpio_assistant) 
{
}

TEST_TEAR_DOWN(gpio_assistant) 
{
}

TEST(gpio_assistant, builds_gpio_pin_select_mask)
{
    uint32_t expected_mask = ( (1ULL<<GPIO_NUM_12) | (1ULL<<GPIO_NUM_0) | (1ULL<<GPIO_NUM_2) ) ;
    uint32_t actual_mask = gpio_build_pin_select_mask(3, GPIO_NUM_12, GPIO_NUM_0, GPIO_NUM_2);

    TEST_ASSERT_EQUAL(expected_mask, actual_mask);
}

TEST_GROUP_RUNNER(gpio_assistant) {
    RUN_TEST_CASE(gpio_assistant, builds_gpio_pin_select_mask);
}
