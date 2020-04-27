#include <esp_event.h>
#include <esp_task.h>
#include <freertos/event_groups.h>


esp_err_t esp_event_handler_register(esp_event_base_t event_base, int32_t event_id,
        esp_event_handler_t event_handler, void* event_handler_arg)
{
    return ESP_OK;
}

esp_err_t esp_event_handler_unregister(esp_event_base_t event_base, int32_t event_id,
        esp_event_handler_t event_handler)
{
    return ESP_OK;
}

esp_err_t esp_event_post(esp_event_base_t event_base, int32_t event_id,
        void* event_data, size_t event_data_size, TickType_t ticks_to_wait)
{
    return ESP_OK;
}


#if CONFIG_ESP_EVENT_POST_FROM_ISR
esp_err_t esp_event_isr_post(esp_event_base_t event_base, int32_t event_id,
        void* event_data, size_t event_data_size, BaseType_t* task_unblocked)
{
    return ESP_OK;
}
#endif


esp_err_t esp_event_loop_create_default()
{
    return ESP_OK;
}

esp_err_t esp_event_loop_delete_default()
{
    return ESP_OK;
}

esp_err_t esp_event_send(system_event_t *event)
{
    return ESP_OK;
}

typedef struct xEventGroupDefinition
{
	EventBits_t uxEventBits;
	List_t xTasksWaitingForBits;		/*< List of tasks waiting for a bit to be set. */

	#if( configUSE_TRACE_FACILITY == 1 )
		UBaseType_t uxEventGroupNumber;
	#endif

	#if( ( configSUPPORT_STATIC_ALLOCATION == 1 ) && ( configSUPPORT_DYNAMIC_ALLOCATION == 1 ) )
		uint8_t ucStaticallyAllocated; /*< Set to pdTRUE if the event group is statically allocated to ensure no attempt is made to free the memory. */
	#endif
} EventGroup_t;

EventGroupHandle_t xEventGroupCreate( void )
{
    EventGroup_t *pxEventBits;
    // pxEventBits = ( EventGroup_t * ) pvPortMalloc( sizeof( EventGroup_t ) );
    return ( EventGroupHandle_t ) pxEventBits;
}

EventBits_t xEventGroupSetBits( EventGroupHandle_t xEventGroup, const EventBits_t uxBitsToSet )
{
    EventBits_t t = 0;
    return t;
}

EventBits_t xEventGroupWaitBits( EventGroupHandle_t xEventGroup, const EventBits_t uxBitsToWaitFor, const BaseType_t xClearOnExit, const BaseType_t xWaitForAllBits, TickType_t xTicksToWait )
{
    EventBits_t t = 0;
    return t;
}
