#include "unity_fixture.h"
#include <stdbool.h>
#include <driver/gpio.h>

#include "internal/indirections.h"

#include "button_server.h"

#include "button_server_connect.h"
#include "internal/button_server_connect_priv.h"

#include "lamp_handler.h"
#include "internal/lamp_handler_priv.h"



#include "fff.h"

DEFINE_FFF_GLOBALS;

FAKE_VALUE_FUNC(esp_err_t, button_server_connect_mock);
FAKE_VALUE_FUNC(esp_err_t, register_lamp_handler_mock, httpd_handle_t);

FAKE_VALUE_FUNC(esp_err_t, mdns_init_mock);
FAKE_VALUE_FUNC(esp_err_t, mdns_hostname_set_mock, const char * );
FAKE_VALUE_FUNC(esp_err_t, mdns_instance_name_set_mock, const char * );
FAKE_VALUE_FUNC(esp_err_t, mdns_service_add_mock, const char * , const char * , const char * , uint16_t , mdns_txt_item_t*, size_t );


TEST_GROUP(button_server);

TEST_SETUP(button_server) 
{
    FFF_RESET_HISTORY();
    RESET_FAKE(button_server_connect_mock);
    RESET_FAKE(register_lamp_handler_mock);

    RESET_FAKE(mdns_init_mock);
    RESET_FAKE(mdns_hostname_set_mock);
    RESET_FAKE(mdns_instance_name_set_mock);
    RESET_FAKE(mdns_service_add_mock);

    button_server_connect = button_server_connect_mock;
    register_lamp_handler = register_lamp_handler_mock;

    mdns_init_impl = mdns_init_mock;
    mdns_hostname_set_impl = mdns_hostname_set_mock;
    mdns_instance_name_set_impl = mdns_instance_name_set_mock;
    mdns_service_add_impl = mdns_service_add_mock;
}

TEST_TEAR_DOWN(button_server) 
{
    button_server_connect = button_server_connect_impl;
    register_lamp_handler = register_lamp_handler_impl;

    mdns_init_impl = mdns_init;
    mdns_hostname_set_impl = mdns_hostname_set;
    mdns_instance_name_set_impl = mdns_instance_name_set;
    mdns_service_add_impl = mdns_service_add;
}


TEST(button_server, start_the_server_calls_button_server_connect)
{
    start_the_server();

    TEST_ASSERT_EQUAL(1, button_server_connect_mock_fake.call_count);
}

TEST(button_server, start_the_server_calls_register_lamp_handler)
{
    start_the_server();

    TEST_ASSERT_EQUAL(1, register_lamp_handler_mock_fake.call_count);
}

TEST(button_server, start_the_server_initializes_mdns)
{
    start_the_server();

    TEST_ASSERT_EQUAL(1, mdns_init_mock_fake.call_count);
    TEST_ASSERT_EQUAL(1, mdns_hostname_set_mock_fake.call_count);
    TEST_ASSERT_EQUAL(1, mdns_instance_name_set_mock_fake.call_count);
    TEST_ASSERT_EQUAL(1, mdns_service_add_mock_fake.call_count);
}

TEST_GROUP_RUNNER(button_server) {
    RUN_TEST_CASE(button_server, start_the_server_calls_button_server_connect);
    RUN_TEST_CASE(button_server, start_the_server_calls_register_lamp_handler);
    RUN_TEST_CASE(button_server, start_the_server_initializes_mdns);
}
