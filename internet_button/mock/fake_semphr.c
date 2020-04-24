
#include "freertos/FreeRTOS.h"
#include "freertos/semphr.h"


QueueHandle_t xQueueGenericCreate( const UBaseType_t uxQueueLength, const UBaseType_t uxItemSize, const uint8_t ucQueueType )
{
    return NULL;
}

BaseType_t xQueueGenericSend( QueueHandle_t xQueue, const void * const pvItemToQueue, TickType_t xTicksToWait, const BaseType_t xCopyPosition )
{
    return pdTRUE;
}

BaseType_t xQueueSemaphoreTake( QueueHandle_t xQueue, TickType_t xTicksToWait )
{
    return pdTRUE;
}

//taskYIELD() is a macro that resolves down to PendSV()
void PendSV(int req)
{
}
