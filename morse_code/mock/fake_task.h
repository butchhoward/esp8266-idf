#ifndef MOCK_TASK_H_
#define MOCK_TASK_H_

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

struct xTaskCreate_call {
  TaskFunction_t pvTaskCode;
  const char *constpcName;
  uint32_t usStackDepth;
  void *constpvParameters;
  UBaseType_t uxPriority;
  TaskHandle_t *constpvCreatedTask;
};

struct xTaskCreate_call *xTaskCreateCall(void);

TickType_t vTaskDelayCall();

#endif
