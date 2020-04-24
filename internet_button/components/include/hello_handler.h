#ifndef HELLO_HANDLER_H
#define HELLO_HANDLER_H

#include <esp_http_server.h>

esp_err_t register_hello_handler(httpd_handle_t server);
esp_err_t unregister_hello_handler(httpd_handle_t server);


#endif

