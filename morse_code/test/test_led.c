#include "unity_fixture.h"
#include "led.h"
#include <stdbool.h>

TEST_GROUP(led);
TEST_SETUP(led) {}
TEST_TEAR_DOWN(led) {}

TEST(led, led1)
{
    TEST_ASSERT_TRUE(false);
}

TEST(led, led2)
{
    TEST_ASSERT_TRUE(false);
}

TEST_GROUP_RUNNER(led) {
    RUN_TEST_CASE(led, led1);
    RUN_TEST_CASE(led, led2);
}
