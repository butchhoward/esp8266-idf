#ifndef CTRL_HANDLER_H
#define CTRL_HANDLER_H

#include <esp_http_server.h>

esp_err_t register_ctrl_handler(httpd_handle_t server);
esp_err_t unregister_ctrl_handler(httpd_handle_t server);


#endif
