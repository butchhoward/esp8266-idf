#include <esp_wifi.h>

ESP_EVENT_DEFINE_BASE(WIFI_EVENT);

esp_err_t esp_wifi_init(const wifi_init_config_t *config)
{
    return ESP_OK;
}
// esp_err_t esp_wifi_deinit(void);
esp_err_t esp_wifi_set_mode(wifi_mode_t mode)
{
    return ESP_OK;
}
// esp_err_t esp_wifi_get_mode(wifi_mode_t *mode);
esp_err_t esp_wifi_start(void)
{
    return ESP_OK;
}
// esp_err_t esp_wifi_stop(void);
// esp_err_t esp_wifi_restore(void);
esp_err_t esp_wifi_connect(void)
{
    return ESP_OK;
}
// esp_err_t esp_wifi_disconnect(void);
// esp_err_t esp_wifi_clear_fast_connect(void);
// esp_err_t esp_wifi_deauth_sta(uint16_t aid);
// esp_err_t esp_wifi_scan_start(const wifi_scan_config_t *config, bool block);
// esp_err_t esp_wifi_scan_stop(void);
// esp_err_t esp_wifi_scan_get_ap_num(uint16_t *number);
// esp_err_t esp_wifi_scan_get_ap_records(uint16_t *number, wifi_ap_record_t *ap_records);
// esp_err_t esp_wifi_sta_get_ap_info(wifi_ap_record_t *ap_info);
// esp_err_t esp_wifi_set_ps(wifi_ps_type_t type);
// esp_err_t esp_wifi_get_ps(wifi_ps_type_t *type);
esp_err_t esp_wifi_set_protocol(wifi_interface_t ifx, uint8_t protocol_bitmap)
{
    return ESP_OK;
}
// esp_err_t esp_wifi_get_protocol(wifi_interface_t ifx, uint8_t *protocol_bitmap);
// esp_err_t esp_wifi_set_bandwidth(wifi_interface_t ifx, wifi_bandwidth_t bw);
// esp_err_t esp_wifi_get_bandwidth(wifi_interface_t ifx, wifi_bandwidth_t *bw);
// esp_err_t esp_wifi_set_channel(uint8_t primary, wifi_second_chan_t second);
// esp_err_t esp_wifi_get_channel(uint8_t *primary, wifi_second_chan_t *second);
// esp_err_t esp_wifi_set_country(const wifi_country_t *country);
// esp_err_t esp_wifi_get_country(wifi_country_t *country);
// esp_err_t esp_wifi_set_mac(wifi_interface_t ifx, const uint8_t mac[6]);
// esp_err_t esp_wifi_get_mac(wifi_interface_t ifx, uint8_t mac[6]);
// typedef void (* wifi_promiscuous_cb_t)(void *buf, wifi_promiscuous_pkt_type_t type);
// esp_err_t esp_wifi_set_promiscuous_rx_cb(wifi_promiscuous_cb_t cb);
// esp_err_t esp_wifi_set_promiscuous(bool en);
// esp_err_t esp_wifi_get_promiscuous(bool *en);
// esp_err_t esp_wifi_set_promiscuous_filter(const wifi_promiscuous_filter_t *filter);
// esp_err_t esp_wifi_get_promiscuous_filter(wifi_promiscuous_filter_t *filter);
esp_err_t esp_wifi_set_config(wifi_interface_t interface, wifi_config_t *conf)
{
    return ESP_OK;
}
// esp_err_t esp_wifi_set_promiscuous_ctrl_filter(const wifi_promiscuous_filter_t *filter);
// esp_err_t esp_wifi_get_promiscuous_ctrl_filter(wifi_promiscuous_filter_t *filter);
// esp_err_t esp_wifi_get_config(wifi_interface_t interface, wifi_config_t *conf);
// esp_err_t esp_wifi_ap_get_sta_list(wifi_sta_list_t *sta);
esp_err_t esp_wifi_set_storage(wifi_storage_t storage)
{
    return ESP_OK;
}
// esp_err_t esp_wifi_set_auto_connect(bool en) __attribute__ ((deprecated));
// esp_err_t esp_wifi_get_auto_connect(bool *en) __attribute__ ((deprecated));
// esp_err_t esp_wifi_set_vendor_ie(bool enable, wifi_vendor_ie_type_t type, wifi_vendor_ie_id_t idx, const void *vnd_ie);
// esp_err_t esp_wifi_set_vendor_ie_cb(esp_vendor_ie_cb_t cb, void *ctx);
// esp_err_t esp_wifi_set_max_tx_power(int8_t power);
// esp_err_t esp_wifi_get_max_tx_power(int8_t *power);
// esp_err_t esp_wifi_set_event_mask(uint32_t mask);
// esp_err_t esp_wifi_get_event_mask(uint32_t *mask);
// esp_err_t esp_wifi_80211_tx(wifi_interface_t ifx, const void *buffer, int len, bool en_sys_seq);
