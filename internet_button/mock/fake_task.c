#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

void vTaskDelay(const TickType_t xTicksToDelay) PRIVILEGED_FUNCTION 
{
}

BaseType_t xTaskCreate(	TaskFunction_t pxTaskCode,
                        const char * const pcName,		/*lint !e971 Unqualified char types are allowed for strings and single characters only. */
                        const configSTACK_DEPTH_TYPE usStackDepth,
                        void * const pvParameters,
                        UBaseType_t uxPriority,
                        TaskHandle_t * const pxCreatedTask )
{
    return pdPASS;
}
