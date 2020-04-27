#include <esp_http_server.h>

esp_err_t  httpd_start(httpd_handle_t *handle, const httpd_config_t *config)
{
    return ESP_OK;
}

esp_err_t httpd_stop(httpd_handle_t handle)
{
    return ESP_OK;
}

esp_err_t httpd_register_uri_handler(httpd_handle_t handle,
                                     const httpd_uri_t *uri_handler)
{
    return ESP_OK;
}

esp_err_t httpd_unregister_uri_handler(httpd_handle_t handle,
                                       const char *uri, httpd_method_t method)
{
    return ESP_OK;
}

esp_err_t httpd_resp_send(httpd_req_t *r, const char *buf, ssize_t buf_len)
{
    return ESP_OK;
}
esp_err_t httpd_resp_send_500(httpd_req_t *r)
{
    return ESP_OK;
}
esp_err_t httpd_unregister_uri(httpd_handle_t handle, const char* uri)
{
    return ESP_OK;
}

