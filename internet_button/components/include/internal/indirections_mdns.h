#ifndef INDIRECTIONS_MDNS_H
#define INDIRECTIONS_MDNS_H

#include <mdns.h>

extern esp_err_t (*mdns_init_impl)(void);
extern esp_err_t (*mdns_hostname_set_impl)(const char * hostname);
extern esp_err_t (*mdns_instance_name_set_impl)(const char * instance_name);
extern esp_err_t (*mdns_service_add_impl)(const char * instance_name, const char * service_type, const char * proto, uint16_t port, mdns_txt_item_t txt[], size_t num_items);

#endif
