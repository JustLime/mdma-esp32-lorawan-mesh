#include "Arduino.h"
#include "heltec.h"

UBaseType_t uxPriority = 1;
uint32_t usStackDepth = 10000;
void *pvParameters = NULL;
TaskHandle_t *pvCreatedTask = NULL;

static long BAND = 868E6L;

void core0Task(void *parameter)
{
  while (true)
  {
    // Core 0 task logic here
    Heltec.display->clear();
    Heltec.display->drawStringMaxWidth(0, 0, 128, "CPU0");
    Heltec.display->display();
    Serial.println("CPU0");

    vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay for 1 second
  }
}

void core1Task(void *parameter)
{
  while (true)
  {
    // Core 1 task logic here
    Heltec.display->clear();
    Heltec.display->drawStringMaxWidth(0, 0, 128, "CPU1");
    Heltec.display->display();
    Serial.println("CPU1");

    vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay for 1 second
  }
}

void setup()
{
  Heltec.begin(BAND);
  Serial.begin(115200);

  Heltec.display->init();
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  delay(1500);
  Heltec.display->clear();

  xTaskCreatePinnedToCore(core0Task, "Core 0 Task", usStackDepth, pvParameters, uxPriority, pvCreatedTask, 0);
  xTaskCreatePinnedToCore(core1Task, "Core 1 Task", usStackDepth, pvParameters, uxPriority, pvCreatedTask, 1);
}

void loop()
{
  // Empty loop as tasks are scheduled by FreeRTOS
  vTaskDelay(1 / portTICK_PERIOD_MS);
}
