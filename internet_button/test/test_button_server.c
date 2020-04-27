#include "unity_fixture.h"
#include <stdbool.h>
#include <driver/gpio.h>

#include "button_server.h"

#include "button_server_connect.h"
#include "internal/button_server_connect_priv.h"

#include "lamp_handler.h"
#include "internal/lamp_handler_priv.h"



#include "fff.h"

DEFINE_FFF_GLOBALS;

FAKE_VALUE_FUNC(esp_err_t, button_server_connect_mock);
FAKE_VALUE_FUNC(esp_err_t, register_lamp_handler_mock, httpd_handle_t);


TEST_GROUP(button_server);

TEST_SETUP(button_server) 
{
    FFF_RESET_HISTORY();
    RESET_FAKE(button_server_connect_mock);
    RESET_FAKE(register_lamp_handler_mock);
}

TEST_TEAR_DOWN(button_server) 
{
}


TEST(button_server, start_the_server_calls_button_server_connect)
{
    button_server_connect = button_server_connect_mock;
    start_the_server();

    TEST_ASSERT_EQUAL(1, button_server_connect_mock_fake.call_count);
    button_server_connect = button_server_connect_impl;
}

TEST(button_server, start_the_server_calls_register_lamp_handler)
{
    register_lamp_handler = register_lamp_handler_mock;
    start_the_server();

    TEST_ASSERT_EQUAL(1, register_lamp_handler_mock_fake.call_count);
    register_lamp_handler = register_lamp_handler_impl;
}

TEST_GROUP_RUNNER(button_server) {
    RUN_TEST_CASE(button_server, start_the_server_calls_button_server_connect);
    RUN_TEST_CASE(button_server, start_the_server_calls_register_lamp_handler);
}
