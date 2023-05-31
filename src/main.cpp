#include "ESP32_LoRaWAN.h"
#include "Arduino.h"

UBaseType_t uxPriority = 1;
uint32_t usStackDepth = 10000;
void *pvParameters = NULL;
TaskHandle_t *pvCreatedTask = NULL;

void core1Task(void *parameter)
{
  while (true)
  {
    // Core 1 task logic here
    vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay for 1 second
  }
}

void core0Task(void *parameter)
{
  while (true)
  {
    // Core 0 task logic here
    vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay for 1 second
  }
}

void setup()
{
  Serial.begin(115200);

  xTaskCreatePinnedToCore(core1Task, "Core 1 Task", usStackDepth, pvParameters, uxPriority, pvCreatedTask, 1);
  xTaskCreatePinnedToCore(core0Task, "Core 0 Task", usStackDepth, pvParameters, uxPriority, pvCreatedTask, 0);
}

void loop()
{
  // Empty loop as tasks are scheduled by FreeRTOS
  vTaskDelay(1);
}
