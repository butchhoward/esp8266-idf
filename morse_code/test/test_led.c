#include "unity_fixture.h"
#include "led.h"
#include <stdbool.h>

#include "fff.h"

DEFINE_FFF_GLOBALS;

FAKE_VALUE_FUNC(esp_err_t, gpio_set_direction_mock, gpio_num_t, gpio_mode_t);
FAKE_VALUE_FUNC(esp_err_t, gpio_set_level_mock, gpio_num_t, uint32_t);

TEST_GROUP(led);

TEST_SETUP(led) 
{
    RESET_FAKE(gpio_set_direction_mock);
}

TEST_TEAR_DOWN(led) 
{

}

TEST(led, led_setup_sets_direction_to_output)
{
    gpio_set_direction_impl = gpio_set_direction_mock;
    led_setup();

    TEST_ASSERT_EQUAL(1, gpio_set_direction_mock_fake.call_count);
    TEST_ASSERT_EQUAL(LED_BUILTIN, gpio_set_direction_mock_fake.arg0_val);
    TEST_ASSERT_EQUAL(GPIO_MODE_OUTPUT, gpio_set_direction_mock_fake.arg1_val);
}

TEST(led, led_setup_sets_level_to_high)
{
    gpio_set_level_impl = gpio_set_level_mock;
    led_setup();

    TEST_ASSERT_EQUAL(1, gpio_set_level_mock_fake.call_count);
    TEST_ASSERT_EQUAL(LED_BUILTIN, gpio_set_level_mock_fake.arg0_val);
    TEST_ASSERT_EQUAL(HIGH, gpio_set_level_mock_fake.arg1_val);
}


TEST_GROUP_RUNNER(led) {
    RUN_TEST_CASE(led, led_setup_sets_direction_to_output);
    RUN_TEST_CASE(led, led_setup_sets_level_to_high);
}
