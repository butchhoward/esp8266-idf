#include "fake_task.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <string.h>

struct xTaskCreate_call xtaskcreate_call;
TickType_t vtaskdelay_call = 0;

#ifdef xTaskCreatePinnedToCore
    #undef xTaskCreatePinnedToCore
#endif
BaseType_t xTaskCreatePinnedToCore(TaskFunction_t pvTaskCode,
                                   const char *const pcName,
                                   const uint32_t usStackDepth,
                                   void *const pvParameters,
                                   UBaseType_t uxPriority,
                                   TaskHandle_t *const pvCreatedTask,
                                   const BaseType_t xCoreID) {
  xtaskcreate_call.pvTaskCode = pvTaskCode;
  xtaskcreate_call.constpcName = pcName;
  xtaskcreate_call.usStackDepth = usStackDepth;
  xtaskcreate_call.constpvParameters = pvParameters;
  xtaskcreate_call.uxPriority = uxPriority;
  xtaskcreate_call.constpvCreatedTask = pvCreatedTask;
  return pdPASS;
}

struct xTaskCreate_call *xTaskCreateCall(void) {
  return &xtaskcreate_call;
}

void vTaskDelay(const TickType_t xTicksToDelay) PRIVILEGED_FUNCTION {
  vtaskdelay_call = xTicksToDelay;
}

TickType_t vTaskDelayCall() { return vtaskdelay_call; }
