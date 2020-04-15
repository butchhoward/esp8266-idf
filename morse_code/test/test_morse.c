#include "unity_fixture.h"
#include <stdbool.h>
#include "fff.h"

#include "led.h"
#include "led_priv.h"
#include "morse.h"
#include "morse_priv.h"

DEFINE_FFF_GLOBALS;

FAKE_VOID_FUNC(vTaskDelay_mock,const TickType_t);

FAKE_VOID_FUNC(morse_dot_mock);
FAKE_VOID_FUNC(morse_dash_mock);
FAKE_VOID_FUNC(morse_dot_delay_mock);
FAKE_VOID_FUNC(morse_dash_delay_mock);
FAKE_VOID_FUNC(morse_letter_mock, const char);

FAKE_VOID_FUNC(led_on_mock);
FAKE_VOID_FUNC(led_off_mock);

TEST_GROUP(morse);

TEST_SETUP(morse) 
{
    FFF_RESET_HISTORY();
    RESET_FAKE(vTaskDelay_mock);

    RESET_FAKE(morse_dot_mock);
    RESET_FAKE(morse_dash_mock);
    RESET_FAKE(morse_dot_delay_mock);
    RESET_FAKE(morse_dash_delay_mock);
    RESET_FAKE(morse_letter_mock);

    RESET_FAKE(led_on_mock);
    RESET_FAKE(led_off_mock);
}

TEST_TEAR_DOWN(morse) 
{
    vTaskDelay_impl = vTaskDelay;

    morse_dot = morse_dot_impl;
    morse_dash = morse_dash_impl;
    morse_dot_delay = morse_dot_delay_impl;
    morse_dash_delay = morse_dash_delay_impl;
    morse_letter = morse_letter_impl;

    led_on = led_on_impl;
    led_off = led_off_impl;
}

TEST(morse, dot_delay_delays_one_dot_time)
{
    vTaskDelay_impl = vTaskDelay_mock;
    morse_dot_delay();

    TEST_ASSERT_EQUAL(1, vTaskDelay_mock_fake.call_count);
    TEST_ASSERT_EQUAL(DOT_TIME / portTICK_RATE_MS, vTaskDelay_mock_fake.arg0_history[0]);
}

TEST(morse, dash_delay_delays_one_dash_time)
{
    vTaskDelay_impl = vTaskDelay_mock;
    morse_dash_delay();

    TEST_ASSERT_EQUAL(1, vTaskDelay_mock_fake.call_count);
    TEST_ASSERT_EQUAL(DASH_TIME / portTICK_RATE_MS, vTaskDelay_mock_fake.arg0_history[0]);
}

TEST(morse, dot_turns_led_on_delays_dot_time_turns_led_off)
{
    led_on = led_on_mock;
    led_off = led_off_mock;
    morse_dot_delay = morse_dot_delay_mock;

    morse_dot();

    TEST_ASSERT_EQUAL(fff.call_history[0], (void *)led_on);
    TEST_ASSERT_EQUAL(fff.call_history[1], (void *)morse_dot_delay);
    TEST_ASSERT_EQUAL(fff.call_history[2], (void *)led_off);

}

TEST(morse, dash_turns_led_on_delays_dash_time_turns_led_off)
{
    led_on = led_on_mock;
    led_off = led_off_mock;
    morse_dash_delay = morse_dash_delay_mock;

    morse_dash();

    TEST_ASSERT_EQUAL(fff.call_history[0], (void *)led_on);
    TEST_ASSERT_EQUAL(fff.call_history[1], (void *)morse_dash_delay);
    TEST_ASSERT_EQUAL(fff.call_history[2], (void *)led_off);

}

TEST(morse, letter_S_does_DOT_DOT_DOT)
{
    morse_dot = morse_dot_mock;
    morse_letter('S');

    TEST_ASSERT_EQUAL(fff.call_history[0], (void *)morse_dot);
    TEST_ASSERT_EQUAL(fff.call_history[1], (void *)morse_dot);
    TEST_ASSERT_EQUAL(fff.call_history[2], (void *)morse_dot);
}

TEST(morse, letter_O_does_DASH_DASH_DASH)
{
    morse_dash = morse_dash_mock;
    morse_letter('O');

    TEST_ASSERT_EQUAL(fff.call_history[0], (void *)morse_dash);
    TEST_ASSERT_EQUAL(fff.call_history[1], (void *)morse_dash);
    TEST_ASSERT_EQUAL(fff.call_history[2], (void *)morse_dash);

}

TEST(morse, letter_R_does_DOT_DASH_DOT)
{
    morse_dash = morse_dash_mock;
    morse_dot = morse_dot_mock;
    morse_letter('R');

    TEST_ASSERT_EQUAL(fff.call_history[0], (void *)morse_dot);
    TEST_ASSERT_EQUAL(fff.call_history[1], (void *)morse_dash);
    TEST_ASSERT_EQUAL(fff.call_history[2], (void *)morse_dot);
}

//...test the entire alphabet...

TEST(morse, word_calls_letter_for_each_letter_in_word)
{
    morse_letter = morse_letter_mock;

    morse_word("SOS");

    TEST_ASSERT_EQUAL('S', morse_letter_mock_fake.arg0_history[0]);
    TEST_ASSERT_EQUAL('O', morse_letter_mock_fake.arg0_history[1]);
    TEST_ASSERT_EQUAL('S', morse_letter_mock_fake.arg0_history[2]);
}

TEST_GROUP_RUNNER(morse) {
    RUN_TEST_CASE(morse, dot_delay_delays_one_dot_time);
    RUN_TEST_CASE(morse, dash_delay_delays_one_dash_time);

    RUN_TEST_CASE(morse, dot_turns_led_on_delays_dot_time_turns_led_off);
    RUN_TEST_CASE(morse, dash_turns_led_on_delays_dash_time_turns_led_off);
    
    RUN_TEST_CASE(morse, letter_S_does_DOT_DOT_DOT);
    RUN_TEST_CASE(morse, letter_O_does_DASH_DASH_DASH);
    RUN_TEST_CASE(morse, letter_R_does_DOT_DASH_DOT);

    RUN_TEST_CASE(morse, word_calls_letter_for_each_letter_in_word);
}
