#include "internal/indirections_mdns.h"

esp_err_t (*mdns_init_impl)(void) = mdns_init;
esp_err_t (*mdns_hostname_set_impl)(const char * hostname) = mdns_hostname_set;
esp_err_t (*mdns_instance_name_set_impl)(const char * instance_name) = mdns_instance_name_set;
esp_err_t (*mdns_service_add_impl)(const char * instance_name, const char * service_type, const char * proto, uint16_t port, mdns_txt_item_t txt[], size_t num_items) = mdns_service_add;
