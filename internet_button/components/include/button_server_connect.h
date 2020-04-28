#ifndef BUTTON_SERVER_CONNECT_H
#define BUTTON_SERVER_CONNECT_H

#include <lwip/ip4_addr.h>
#include <esp_err.h>

extern esp_err_t (*button_server_connect)(void);

#endif
