#include "lamp_handler.h"
#include "relay.h"
#include "gpio_assistant.h"

#include <sys/param.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_event.h"
#include <esp_timer.h>
#include "nvs.h"
#include "nvs_flash.h"

#include <esp_http_server.h>

static const char *TAG="lamp_handler";

static const char* HELLO_BACK_AT_YA=
"<!DOCTYPE html>"
"<html>"
""
"<head>"
"    <title>"
"        Knitting Lamp"
"    </title> "
"      "
"    <!-- Style to create button -->"
"    <style> "
"html, body {"
"  margin: 0;"
"  padding: 0;"
"  height: 100%;"
"}"
""
"body {"
"  display: flex; /* or css grid for more intricate layouts */"
"  flex-direction: column;"
"}"
""
"#top {"
"  background-color: black;"
"  height: 150px;"
"  border-bottom: 3px solid Crimson;"
"}"
""
"#pagewrap {"
"  background-color: black;"
"  flex-grow: 1; /* make it stretch to the bottom even if little content */"
"  overflow-y: scroll; /* optional */"
"}"
"        .LAMPBUTTON { "
"            background-color: LightGreen; "
"            border: 2px solid black; "
"            color: black; "
"            padding: 5px 10px; "
"            text-align: center; "
"            display: inline-block; "
"            font-size: 20px; "
"            margin: 10px 30px; "
"            cursor: pointer; "
"            text-decoration:none;"
"            width:80vw;"
"            height:30vh;"
"        }"
"        .LAMPBUTTON_RED {"
"            background-color: LightCoral; "
"        }"
"    </style>"
"</head>"
""
"<body>"
"    <h1>Knitting Lamp</h1>"
"<div id=pagewrap>"
"    <div><a href=\"http://10.10.1.252/lamp/on\" class=\"LAMPBUTTON\">"
"        Lamp ON"
"    </a></div> "
"    <div><a href=\"http://10.10.1.252/lamp/off\" class=\"LAMPBUTTON LAMPBUTTON_RED\">"
"        Lamp OFF"
"    </a></div>"
"</div>"
"</body>"
""
"</html>";

#define RELAY_GPIO GPIO_NUM_12

static void configure_the_gpio_to_use()
{
    ESP_LOGI(TAG, "configure_the_gpio_to_use");

    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = gpio_build_pin_select_mask(1, RELAY_GPIO);
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    if (gpio_config(&io_conf) != ESP_OK)
    {
       ESP_LOGI(TAG, "configure_the_gpio_to_use failed\n");
    }
}


typedef struct lamp_user_ctx_t 
{
    void* relay_config;
    unsigned int on_count;
    unsigned int off_count;
    int64_t time_last_change;
} lamp_user_ctx_t;


static esp_err_t lamp_get_response(httpd_req_t *req)
{

    /* Send response with custom headers and body set as the
     * string passed in user context*/
    const char* resp_str = (const char*)HELLO_BACK_AT_YA;
    httpd_resp_send(req, resp_str, strlen(resp_str));

    return ESP_OK;
}

static esp_err_t lamp_on_handler(httpd_req_t *req)
{
    ESP_LOGI(TAG, "lamp_on_handler");

    lamp_user_ctx_t* lamp_ctx = (lamp_user_ctx_t*)(req->user_ctx);

    relay_on(lamp_ctx->relay_config);

    lamp_ctx->on_count++;

    lamp_ctx->time_last_change = esp_timer_get_time();

    return lamp_get_response(req);

}

static esp_err_t lamp_off_handler(httpd_req_t *req)
{
    ESP_LOGI(TAG, "lamp_off_handler");

    lamp_user_ctx_t* lamp_ctx = (lamp_user_ctx_t*)(req->user_ctx);

    relay_off(lamp_ctx->relay_config);

    lamp_ctx->off_count++;

    lamp_ctx->time_last_change = esp_timer_get_time();

    return lamp_get_response(req);
}

static esp_err_t lamp_nothing_handler(httpd_req_t *req)
{
    ESP_LOGI(TAG, "lamp_nothing_handler");

    return lamp_get_response(req);
}



lamp_user_ctx_t lamp_ctx = {
    .relay_config = NULL,
    .on_count = 0,
    .off_count = 0,
    .time_last_change = 0
};

httpd_uri_t lamp_off = {
    .uri       = "/lamp/off",
    .method    = HTTP_GET,
    .handler   = lamp_off_handler,
    .user_ctx  = &lamp_ctx
};

httpd_uri_t lamp_on = {
    .uri       = "/lamp/on",
    .method    = HTTP_GET,
    .handler   = lamp_on_handler,
    .user_ctx  = &lamp_ctx
};

httpd_uri_t lamp_nothing = {
    .uri       = "/",
    .method    = HTTP_GET,
    .handler   = lamp_nothing_handler,
    .user_ctx  = &lamp_ctx
};

esp_err_t register_lamp_handler(httpd_handle_t server)
{
    esp_err_t err = ESP_OK;
    lamp_ctx.time_last_change =  esp_timer_get_time();
    configure_the_gpio_to_use();
    lamp_ctx.relay_config = relay_setup_mode(RELAY_GPIO, RELAY_ACTIVE_HIGH);

    httpd_register_uri_handler(server, &lamp_on);
    httpd_register_uri_handler(server, &lamp_off);
    httpd_register_uri_handler(server, &lamp_nothing);

    return err;
}

esp_err_t unregister_lamp_handler(httpd_handle_t server)
{
    esp_err_t err = ESP_OK;
    httpd_unregister_uri(server, lamp_on.uri);
    httpd_unregister_uri(server, lamp_off.uri);
    httpd_unregister_uri(server, lamp_nothing.uri);

    relay_cleanup(lamp_ctx.relay_config);
    lamp_ctx.relay_config = NULL;

    return err;
}
