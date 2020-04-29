#include "button_server.h"
#include "button_server_connect.h"
#include "lamp_handler.h"
#include "internal/indirections_mdns.h"
#include "sdkconfig.h"
#include <sys/param.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <esp_err.h>
#include "esp_system.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_event.h"
#include "nvs.h"
#include "nvs_flash.h"
#include <esp_http_server.h>
#include <mdns.h>

static const char *TAG = "button_server";

httpd_handle_t start_webserver(void)
{
    httpd_handle_t server = NULL;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();

    // Start the httpd server
    ESP_LOGI(TAG, "Starting server on port: '%d'", config.server_port);
    if (httpd_start(&server, &config) == ESP_OK) {
        // Set URI handlers
        ESP_LOGI(TAG, "Registering URI handlers");
        register_lamp_handler(server);
        return server;
    }

    ESP_LOGI(TAG, "Error starting server!");
    return NULL;
}

void stop_webserver(httpd_handle_t server)
{
    // Stop the httpd server
    httpd_stop(server);
}

static httpd_handle_t server = NULL;

static void disconnect_handler(void* arg, esp_event_base_t event_base, 
                               int32_t event_id, void* event_data)
{
    httpd_handle_t* server = (httpd_handle_t*) arg;
    if (*server) {
        ESP_LOGI(TAG, "Stopping webserver");
        stop_webserver(*server);
        *server = NULL;
    }
}

static void connect_handler(void* arg, esp_event_base_t event_base, 
                            int32_t event_id, void* event_data)
{
    httpd_handle_t* server = (httpd_handle_t*) arg;
    if (*server == NULL) {
        ESP_LOGI(TAG, "Starting webserver");
        *server = start_webserver();
    }
}


static void initialise_mdns(void)
{
    ESP_ERROR_CHECK_WITHOUT_ABORT( mdns_init_impl() );
    ESP_ERROR_CHECK_WITHOUT_ABORT( mdns_hostname_set_impl(CONFIG_BUTTON_MDNS_HOSTNAME) );
    ESP_ERROR_CHECK_WITHOUT_ABORT( mdns_instance_name_set_impl(CONFIG_BUTTON_MDNS_INSTANCE) );
    ESP_ERROR_CHECK_WITHOUT_ABORT( mdns_service_add_impl(NULL, "_http", "_tcp", 80, NULL, 0) );
}


void start_the_server()
{
    ESP_ERROR_CHECK_WITHOUT_ABORT(nvs_flash_init());
    ESP_ERROR_CHECK_WITHOUT_ABORT(esp_netif_init());
    ESP_ERROR_CHECK_WITHOUT_ABORT(esp_event_loop_create_default());

    ESP_ERROR_CHECK_WITHOUT_ABORT(button_server_connect());
    initialise_mdns();

    ESP_ERROR_CHECK_WITHOUT_ABORT(esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &connect_handler, &server));
    ESP_ERROR_CHECK_WITHOUT_ABORT(esp_event_handler_register(WIFI_EVENT, WIFI_EVENT_STA_DISCONNECTED, &disconnect_handler, &server));

    server = start_webserver();
}
