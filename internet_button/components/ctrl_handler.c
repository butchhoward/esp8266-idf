#include "ctrl_handler.h"
#include "hello_handler.h"
#include "echo_handler.h"

#include <sys/param.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_event.h"
#include "nvs.h"
#include "nvs_flash.h"

#include <esp_http_server.h>

static const char *TAG="ctrl_handler";


/* An HTTP PUT handler. This demonstrates realtime
 * registration and deregistration of URI handlers
 */
esp_err_t ctrl_put_handler(httpd_req_t *req)
{
    char buf;
    int ret;

    if ((ret = httpd_req_recv(req, &buf, 1)) <= 0) {
        if (ret == HTTPD_SOCK_ERR_TIMEOUT) {
            httpd_resp_send_408(req);
        }
        return ESP_FAIL;
    }

    if (buf == '0') {
        /* Handler can be unregistered using the uri string */
        ESP_LOGI(TAG, "Unregistering /hello and /echo URIs");
        unregister_hello_handler(req->handle);
        unregister_echo_handler(req->handle);
    }
    else {
        ESP_LOGI(TAG, "Registering /hello and /echo URIs");
        register_hello_handler(req->handle);
        register_echo_handler(req->handle);
    }

    /* Respond with empty body */
    httpd_resp_send(req, NULL, 0);
    return ESP_OK;
}

httpd_uri_t ctrl = {
    .uri       = "/ctrl",
    .method    = HTTP_PUT,
    .handler   = ctrl_put_handler,
    .user_ctx  = NULL
};

esp_err_t register_ctrl_handler(httpd_handle_t server)
{
    return httpd_register_uri_handler(server, &ctrl);
}

esp_err_t unregister_ctrl_handler(httpd_handle_t server)
{
    return httpd_unregister_uri(server, ctrl.uri);
}
