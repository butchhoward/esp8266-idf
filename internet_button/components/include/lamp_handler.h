#ifndef LAMP_HANDLER_H
#define LAMP_HANDLER_H

#include <esp_http_server.h>

esp_err_t register_lamp_handler(httpd_handle_t server);
esp_err_t unregister_lamp_handler(httpd_handle_t server);


#endif

