#include "unity_fixture.h"
#include <stdbool.h>
#include "fff.h"

#include "morse.h"
#include "internal/morse_priv.h"

#include "leds.h"
#include "internal/leds_priv.h"

DEFINE_FFF_GLOBALS;

FAKE_VOID_FUNC(vTaskDelay_mock,const TickType_t);

FAKE_VOID_FUNC(morse_dot_mock, void*);
FAKE_VOID_FUNC(morse_dash_mock, void* );
FAKE_VOID_FUNC(morse_dot_delay_mock);
FAKE_VOID_FUNC(morse_dash_delay_mock);
FAKE_VOID_FUNC(morse_letter_mock, void*, const char);

FAKE_VOID_FUNC(led_on_mock,void*);
FAKE_VOID_FUNC(led_off_mock,void*);

TEST_GROUP(morse);


void* led_config = 0;
void* morse_config = 0;

TEST_SETUP(morse) 
{
    led_config = leds_setup(LEDS_BUILTIN_RED);
    morse_config = morse_setup(led_config);

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

    leds_on = leds_on_impl;
    leds_off = leds_off_impl;

    morse_cleanup(morse_config);
}

TEST(morse, configure_defines_led_to_use)
{
    TEST_ASSERT_NOT_NULL(morse_config);
    TEST_ASSERT_EQUAL(led_config, ((morse_config_t*)morse_config)->led_config);
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

    leds_on = led_on_mock;
    leds_off = led_off_mock;
    morse_dot_delay = morse_dot_delay_mock;

    morse_dot(morse_config);

    TEST_ASSERT_EQUAL(fff.call_history[0], (void *)leds_on);
    TEST_ASSERT_EQUAL(fff.call_history[1], (void *)morse_dot_delay);
    TEST_ASSERT_EQUAL(fff.call_history[2], (void *)leds_off);


}

TEST(morse, dash_turns_led_on_delays_dash_time_turns_led_off)
{
    leds_on = led_on_mock;
    leds_off = led_off_mock;
    morse_dash_delay = morse_dash_delay_mock;

    morse_dash(morse_config);

    TEST_ASSERT_EQUAL(fff.call_history[0], (void *)leds_on);
    TEST_ASSERT_EQUAL(fff.call_history[1], (void *)morse_dash_delay);
    TEST_ASSERT_EQUAL(fff.call_history[2], (void *)leds_off);

}

TEST(morse, letter_S_does_DOT_DOT_DOT)
{
    morse_dot = morse_dot_mock;
    morse_letter(morse_config, 'S');

    TEST_ASSERT_EQUAL(fff.call_history[0], (void *)morse_dot);
    TEST_ASSERT_EQUAL(fff.call_history[1], (void *)morse_dot);
    TEST_ASSERT_EQUAL(fff.call_history[2], (void *)morse_dot);
}

TEST(morse, letter_O_does_DASH_DASH_DASH)
{
    morse_dash = morse_dash_mock;
    morse_letter(morse_config, 'O');

    TEST_ASSERT_EQUAL(fff.call_history[0], (void *)morse_dash);
    TEST_ASSERT_EQUAL(fff.call_history[1], (void *)morse_dash);
    TEST_ASSERT_EQUAL(fff.call_history[2], (void *)morse_dash);

}

TEST(morse, letter_R_does_DOT_DASH_DOT)
{
    morse_dash = morse_dash_mock;
    morse_dot = morse_dot_mock;
    morse_letter(morse_config, 'R');

    TEST_ASSERT_EQUAL(fff.call_history[0], (void *)morse_dot);
    TEST_ASSERT_EQUAL(fff.call_history[1], (void *)morse_dash);
    TEST_ASSERT_EQUAL(fff.call_history[2], (void *)morse_dot);
}

//...test the entire alphabet...

TEST(morse, word_calls_letter_for_each_letter_in_word)
{
    morse_letter = morse_letter_mock;

    morse_word(morse_config, "SOS");

    TEST_ASSERT_EQUAL('S', morse_letter_mock_fake.arg1_history[0]);
    TEST_ASSERT_EQUAL('O', morse_letter_mock_fake.arg1_history[1]);
    TEST_ASSERT_EQUAL('S', morse_letter_mock_fake.arg1_history[2]);
}

TEST_GROUP_RUNNER(morse) {
    RUN_TEST_CASE(morse, configure_defines_led_to_use);

    RUN_TEST_CASE(morse, dot_delay_delays_one_dot_time);
    RUN_TEST_CASE(morse, dash_delay_delays_one_dash_time);

    RUN_TEST_CASE(morse, dot_turns_led_on_delays_dot_time_turns_led_off);
    RUN_TEST_CASE(morse, dash_turns_led_on_delays_dash_time_turns_led_off);
    
    RUN_TEST_CASE(morse, letter_S_does_DOT_DOT_DOT);
    RUN_TEST_CASE(morse, letter_O_does_DASH_DASH_DASH);
    RUN_TEST_CASE(morse, letter_R_does_DOT_DASH_DOT);

    RUN_TEST_CASE(morse, word_calls_letter_for_each_letter_in_word);
}
