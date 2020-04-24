#ifndef ECHO_HANDLER_H
#define ECHO_HANDLER_H

#include <esp_http_server.h>

esp_err_t register_echo_handler(httpd_handle_t server);
esp_err_t unregister_echo_handler(httpd_handle_t server);


#endif
