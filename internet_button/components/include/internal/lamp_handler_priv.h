#ifndef LAMP_HANDLER_PRIV_H
#define LAMP_HANDLER_PRIV_H

#include <sys/types.h>
#include <stdbool.h>
#include <esp_http_server.h>

typedef struct lamp_user_ctx_t 
{
    void* relay_config;
    unsigned int on_count;
    unsigned int off_count;
    int64_t time_last_change;
    int64_t elapsed;
    bool currently_on;
} lamp_user_ctx_t;

esp_err_t register_lamp_handler_impl(httpd_handle_t server);

char* lamp_handler_html_response(const lamp_user_ctx_t* lamp_ctx);

#endif
