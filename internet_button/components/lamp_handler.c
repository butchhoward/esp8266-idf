#include "lamp_handler.h"
#include "internal/lamp_handler_priv.h"

#include "relay.h"
#include "gpio_assistant.h"

#include <sys/param.h>
#include <stdio.h>

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

#define IPSTR_FORMAT "%s"

static const char* HELLO_BACK_AT_YA=
"<!DOCTYPE html>"
"<html>"
    "<head>"
        "<title>Knitting Lamp</title>"
        "<style>"
            "html, body {"
                "margin: 0;"
                "padding: 0;"
                "height: 100%%;"
            "}"
            "body {"
                "display: flex; /* or css grid for more intricate layouts */"
                "flex-direction: column;"
                "text-align: center;"
            "}"
            "#pagewrap {"
                "background-color: black;"
                "flex-grow: 1;"
                "overflow-y: scroll;"
                "display: inline-block;"
            "}"
            ".LAMPBUTTON {"
                "background-color: LightGreen;"
                "border: 2px solid black;"
                "color: black;"
                "padding: 5px 10px;"
                "text-align: center;"
                "display: inline-block;"
                "font-size: 20px; "
                "margin: 10px 30px; "
                "cursor: pointer; "
                "text-decoration:none;"
                "width:80vw;"
                "height:40vh;"
            "}"
            ".OFF_RED {"
                "background-color: LightCoral;"
            "}"
            ".ON_RED {"
                "background-color: red;"
            "}"
            ".OFF_GREEN {"
                "background-color: green;"
            "}"
            ".ON_GREEN {"
                "background-color: LightGreen;"
            "}"
        "</style>"
    "</head>"
    "<body>"
        "<h1>Knitting Lamp</h1>"
        "<div id=pagewrap>"
            "<div><a href=\"http://" IPSTR_FORMAT ".local/lamp/on\" class=\"LAMPBUTTON %s\">Lamp ON</a></div>"
            "<div><a href=\"http://" IPSTR_FORMAT ".local/lamp/off\" class=\"LAMPBUTTON %s\">Lamp OFF</a></div>"
        "</div>"
        "<div><p>Currently: %s</p></div>"
    "</body>"
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
    int64_t elapsed;
    bool currently_on;
} lamp_user_ctx_t;


static esp_err_t lamp_get_response(httpd_req_t *req)
{
    esp_err_t err = ESP_OK;
    lamp_user_ctx_t* lamp_ctx = (lamp_user_ctx_t*)(req->user_ctx);

    ESP_LOGI(TAG, "lamp_get_response DNS:" IPSTR_FORMAT ".local on=%u off=%u %s last=%d elapsed=%d", 
        CONFIG_BUTTON_MDNS_HOSTNAME,
        lamp_ctx->on_count, 
        lamp_ctx->off_count, 
        (lamp_ctx->currently_on ? "ON" : "OFF"),
        (int32_t)(lamp_ctx->time_last_change/1000000LL), 
        (int32_t)(lamp_ctx->elapsed/1000000LL)
    );

    char* resp_str = NULL;
    int ret = asprintf(&resp_str, HELLO_BACK_AT_YA,
        CONFIG_BUTTON_MDNS_HOSTNAME,
        (lamp_ctx->currently_on ? "ON_GREEN" : "OFF_GREEN"),
        CONFIG_BUTTON_MDNS_HOSTNAME,
        (lamp_ctx->currently_on ? "ON_RED" : "OFF_RED"),
        (lamp_ctx->currently_on ? "ON" : "OFF")
    );

    if (ret < 0)
    {
        err = httpd_resp_send_500(req);
    }
    else
    {
        err = httpd_resp_send(req, resp_str, strlen(resp_str));
        free(resp_str);
    }

    return err;
}

static esp_err_t lamp_on_handler(httpd_req_t *req)
{
    ESP_LOGI(TAG, "lamp_on_handler");

    lamp_user_ctx_t* lamp_ctx = (lamp_user_ctx_t*)(req->user_ctx);

    relay_on(lamp_ctx->relay_config);

    lamp_ctx->on_count++;
    lamp_ctx->currently_on = true;
    lamp_ctx->elapsed = esp_timer_get_time() - lamp_ctx->time_last_change;
    lamp_ctx->time_last_change = esp_timer_get_time();

    return lamp_get_response(req);
}

static esp_err_t lamp_off_handler(httpd_req_t *req)
{
    ESP_LOGI(TAG, "lamp_off_handler");

    lamp_user_ctx_t* lamp_ctx = (lamp_user_ctx_t*)(req->user_ctx);

    relay_off(lamp_ctx->relay_config);

    lamp_ctx->off_count++;
    lamp_ctx->currently_on = false;
    lamp_ctx->elapsed = esp_timer_get_time() - lamp_ctx->time_last_change;
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
    .time_last_change = 0,
    .elapsed = 0,
    .currently_on = false
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

esp_err_t (*register_lamp_handler)(httpd_handle_t server) = register_lamp_handler_impl;
esp_err_t register_lamp_handler_impl(httpd_handle_t server)
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
