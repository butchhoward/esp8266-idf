#include "unity_fixture.h"
#include <stdbool.h>
#include "relay.h"
#include "internal/relay_priv.h"

#include <driver/gpio.h>

#include "fff.h"

DEFINE_FFF_GLOBALS;

FAKE_VALUE_FUNC(esp_err_t, relay_gpio_set_direction_mock, gpio_num_t, gpio_mode_t);
FAKE_VALUE_FUNC(esp_err_t, relay_gpio_set_level_mock, gpio_num_t, uint32_t);

TEST_GROUP(relay);

TEST_SETUP(relay) 
{
    FFF_RESET_HISTORY();
    RESET_FAKE(relay_gpio_set_direction_mock);
    RESET_FAKE(relay_gpio_set_level_mock);
    gpio_set_direction_impl = relay_gpio_set_direction_mock;
    gpio_set_level_impl = relay_gpio_set_level_mock;
}

TEST_TEAR_DOWN(relay) 
{
    gpio_set_direction_impl = gpio_set_direction;
    gpio_set_level_impl = gpio_set_level;
}


TEST(relay, off_active_high_sets_level_low)
{
    void *config = relay_setup_mode(GPIO_NUM_5, RELAY_ACTIVE_HIGH);
    RESET_FAKE(relay_gpio_set_direction_mock);
    RESET_FAKE(relay_gpio_set_level_mock);

    relay_off(config);

    TEST_ASSERT_EQUAL(1, relay_gpio_set_level_mock_fake.call_count);
    TEST_ASSERT_EQUAL(GPIO_NUM_5, relay_gpio_set_level_mock_fake.arg0_val);
    TEST_ASSERT_EQUAL(RELAY_LOW_LEVEL, relay_gpio_set_level_mock_fake.arg1_val);

    relay_cleanup(config);
}


TEST(relay, on_active_high_sets_level_high)
{
    void *config = relay_setup_mode(GPIO_NUM_5, RELAY_ACTIVE_HIGH);
    RESET_FAKE(relay_gpio_set_direction_mock);
    RESET_FAKE(relay_gpio_set_level_mock);

    relay_on(config);

    TEST_ASSERT_EQUAL(1, relay_gpio_set_level_mock_fake.call_count);
    TEST_ASSERT_EQUAL(GPIO_NUM_5, relay_gpio_set_level_mock_fake.arg0_val);
    TEST_ASSERT_EQUAL(RELAY_HIGH_LEVEL, relay_gpio_set_level_mock_fake.arg1_val);

    relay_cleanup(config);
}

TEST(relay, on_active_low_sets_level_low)
{
    void *config = relay_setup_mode(GPIO_NUM_5, RELAY_ACTIVE_LOW);
    RESET_FAKE(relay_gpio_set_direction_mock);
    RESET_FAKE(relay_gpio_set_level_mock);

    relay_on(config);

    TEST_ASSERT_EQUAL(1, relay_gpio_set_level_mock_fake.call_count);
    TEST_ASSERT_EQUAL(GPIO_NUM_5, relay_gpio_set_level_mock_fake.arg0_val);
    TEST_ASSERT_EQUAL(RELAY_LOW_LEVEL, relay_gpio_set_level_mock_fake.arg1_val);

    relay_cleanup(config);
}

TEST(relay, off_active_low_sets_level_high)
{
    void *config = relay_setup_mode(GPIO_NUM_5, RELAY_ACTIVE_LOW);
    RESET_FAKE(relay_gpio_set_direction_mock);
    RESET_FAKE(relay_gpio_set_level_mock);

    relay_off(config);

    TEST_ASSERT_EQUAL(1, relay_gpio_set_level_mock_fake.call_count);
    TEST_ASSERT_EQUAL(GPIO_NUM_5, relay_gpio_set_level_mock_fake.arg0_val);
    TEST_ASSERT_EQUAL(RELAY_HIGH_LEVEL, relay_gpio_set_level_mock_fake.arg1_val);

    relay_cleanup(config);
}

TEST_GROUP_RUNNER(relay) {
    RUN_TEST_CASE(relay, off_active_high_sets_level_low);
    RUN_TEST_CASE(relay, on_active_high_sets_level_high);
    RUN_TEST_CASE(relay, on_active_low_sets_level_low);
    RUN_TEST_CASE(relay, off_active_low_sets_level_high);


}
