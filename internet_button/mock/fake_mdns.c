#include <mdns.h>

esp_err_t mdns_init()
{
    return ESP_OK;
}

esp_err_t mdns_hostname_set(const char * hostname)
{
    return ESP_OK;
}

esp_err_t mdns_instance_name_set(const char * instance_name)
{
    return ESP_OK;
}

esp_err_t mdns_service_add(const char * instance_name, const char * service_type, const char * proto, uint16_t port, mdns_txt_item_t txt[], size_t num_items)
{
    return ESP_OK;
}

