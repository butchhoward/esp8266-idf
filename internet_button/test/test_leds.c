#include "unity_fixture.h"
#include "leds.h"
#include "internal/leds_priv.h"
#include <stdbool.h>

#include "fff.h"

DEFINE_FFF_GLOBALS;

FAKE_VALUE_FUNC(esp_err_t, leds_gpio_set_direction_mock, gpio_num_t, gpio_mode_t);
FAKE_VALUE_FUNC(esp_err_t, leds_gpio_set_level_mock, gpio_num_t, uint32_t);

TEST_GROUP(leds);

TEST_SETUP(leds) 
{
    FFF_RESET_HISTORY();
    RESET_FAKE(leds_gpio_set_direction_mock);
    RESET_FAKE(leds_gpio_set_level_mock);
    gpio_set_direction_impl = leds_gpio_set_direction_mock;
    gpio_set_level_impl = leds_gpio_set_level_mock;
}

TEST_TEAR_DOWN(leds) 
{
    gpio_set_direction_impl = gpio_set_direction;
    gpio_set_level_impl = gpio_set_level;
}

TEST(leds, ctor_configures_for_red_led)
{

    void *config = leds_setup(LEDS_GPIO_16);

    TEST_ASSERT_NOT_NULL(config);
    TEST_ASSERT_EQUAL(GPIO_NUM_16, ((leds_config_t*)config)->led_type);

    TEST_ASSERT_EQUAL(1, leds_gpio_set_direction_mock_fake.call_count);
    TEST_ASSERT_EQUAL(GPIO_NUM_16, leds_gpio_set_direction_mock_fake.arg0_val);
    TEST_ASSERT_EQUAL(GPIO_MODE_OUTPUT, leds_gpio_set_direction_mock_fake.arg1_val);

    TEST_ASSERT_EQUAL(1, leds_gpio_set_level_mock_fake.call_count);
    TEST_ASSERT_EQUAL(GPIO_NUM_16, leds_gpio_set_level_mock_fake.arg0_val);
    TEST_ASSERT_EQUAL(HIGH_LEVEL, leds_gpio_set_level_mock_fake.arg1_val);

    leds_cleanup(config);
}

TEST(leds, ctor_configures_for_blue_led)
{

    void *config = leds_setup(LEDS_GPIO_2);

    TEST_ASSERT_NOT_NULL(config);
    TEST_ASSERT_EQUAL(GPIO_NUM_2, ((leds_config_t*)config)->led_type);

    TEST_ASSERT_EQUAL(1, leds_gpio_set_direction_mock_fake.call_count);
    TEST_ASSERT_EQUAL(GPIO_NUM_2, leds_gpio_set_direction_mock_fake.arg0_val);
    TEST_ASSERT_EQUAL(GPIO_MODE_OUTPUT, leds_gpio_set_direction_mock_fake.arg1_val);

    leds_cleanup(config);
}


TEST(leds, dtor_dtors)
{
    void *config = leds_setup(LEDS_GPIO_16);
    TEST_ASSERT_NOT_NULL(config);
    leds_cleanup(config);

    //how do we test that? mock malloc and free?
    TEST_PASS();
}


TEST(leds, on_sets_level_low)
{
    void *config = leds_setup(LEDS_GPIO_16);
    RESET_FAKE(leds_gpio_set_direction_mock);
    RESET_FAKE(leds_gpio_set_level_mock);

    leds_on(config);

    TEST_ASSERT_EQUAL(1, leds_gpio_set_level_mock_fake.call_count);
    TEST_ASSERT_EQUAL(LEDS_GPIO_16, leds_gpio_set_level_mock_fake.arg0_val);
    TEST_ASSERT_EQUAL(LOW_LEVEL, leds_gpio_set_level_mock_fake.arg1_val);

    leds_cleanup(config);
}

TEST(leds, off_sets_level_high)
{
    void *config = leds_setup(LEDS_GPIO_16);
    RESET_FAKE(leds_gpio_set_direction_mock);
    RESET_FAKE(leds_gpio_set_level_mock);

    leds_off(config);

    TEST_ASSERT_EQUAL(1, leds_gpio_set_level_mock_fake.call_count);
    TEST_ASSERT_EQUAL(LEDS_GPIO_16, leds_gpio_set_level_mock_fake.arg0_val);
    TEST_ASSERT_EQUAL(HIGH_LEVEL, leds_gpio_set_level_mock_fake.arg1_val);

    leds_cleanup(config);
}

TEST(leds, ctor_configures_for_led_for_active_high_operation)
{
    void *config = leds_setup_mode(LEDS_GPIO_5, LED_ACTIVE_HIGH);

    TEST_ASSERT_NOT_NULL(config);
    TEST_ASSERT_EQUAL(GPIO_NUM_5, ((leds_config_t*)config)->led_type);
    TEST_ASSERT_EQUAL(LED_ACTIVE_HIGH, ((leds_config_t*)config)->mode);

    TEST_ASSERT_EQUAL(1, leds_gpio_set_direction_mock_fake.call_count);
    TEST_ASSERT_EQUAL(GPIO_NUM_5, leds_gpio_set_direction_mock_fake.arg0_val);
    TEST_ASSERT_EQUAL(GPIO_MODE_OUTPUT, leds_gpio_set_direction_mock_fake.arg1_val);

    leds_cleanup(config);
}

TEST(leds, ctor_configures_for_led_for_active_low_operation)
{
    void *config = leds_setup_mode(LEDS_GPIO_5, LED_ACTIVE_LOW);

    TEST_ASSERT_NOT_NULL(config);
    TEST_ASSERT_EQUAL(GPIO_NUM_5, ((leds_config_t*)config)->led_type);
    TEST_ASSERT_EQUAL(LED_ACTIVE_LOW, ((leds_config_t*)config)->mode);

    TEST_ASSERT_EQUAL(1, leds_gpio_set_direction_mock_fake.call_count);
    TEST_ASSERT_EQUAL(GPIO_NUM_5, leds_gpio_set_direction_mock_fake.arg0_val);
    TEST_ASSERT_EQUAL(GPIO_MODE_OUTPUT, leds_gpio_set_direction_mock_fake.arg1_val);

    leds_cleanup(config);
}

TEST(leds, on_active_high_sets_level_high)
{
    void *config = leds_setup_mode(LEDS_GPIO_5, LED_ACTIVE_HIGH);
    RESET_FAKE(leds_gpio_set_direction_mock);
    RESET_FAKE(leds_gpio_set_level_mock);

    leds_on(config);

    TEST_ASSERT_EQUAL(1, leds_gpio_set_level_mock_fake.call_count);
    TEST_ASSERT_EQUAL(LEDS_GPIO_5, leds_gpio_set_level_mock_fake.arg0_val);
    TEST_ASSERT_EQUAL(HIGH_LEVEL, leds_gpio_set_level_mock_fake.arg1_val);

    leds_cleanup(config);
}

TEST(leds, off_active_high_sets_level_low)
{
    void *config = leds_setup_mode(LEDS_GPIO_5, LED_ACTIVE_HIGH);
    RESET_FAKE(leds_gpio_set_direction_mock);
    RESET_FAKE(leds_gpio_set_level_mock);

    leds_off(config);

    TEST_ASSERT_EQUAL(1, leds_gpio_set_level_mock_fake.call_count);
    TEST_ASSERT_EQUAL(LEDS_GPIO_5, leds_gpio_set_level_mock_fake.arg0_val);
    TEST_ASSERT_EQUAL(LOW_LEVEL, leds_gpio_set_level_mock_fake.arg1_val);

    leds_cleanup(config);
}


TEST_GROUP_RUNNER(leds) {
    RUN_TEST_CASE(leds, ctor_configures_for_red_led);
    RUN_TEST_CASE(leds, ctor_configures_for_blue_led);
    RUN_TEST_CASE(leds, dtor_dtors);
    RUN_TEST_CASE(leds, on_sets_level_low);
    RUN_TEST_CASE(leds, off_sets_level_high);
    RUN_TEST_CASE(leds, ctor_configures_for_led_for_active_high_operation);
    RUN_TEST_CASE(leds, on_active_high_sets_level_high);
    RUN_TEST_CASE(leds, off_active_high_sets_level_low);
}
