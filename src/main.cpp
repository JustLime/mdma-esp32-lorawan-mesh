#include "Arduino.h"
#include "heltec.h"

UBaseType_t uxPriority = 1;
uint32_t usStackDepth = 10000;
void *pvParameters = NULL;
TaskHandle_t *pvCreatedTask = NULL;
int counter = 0;
String message;

static long BAND = 868E6L;

void sendMessageToNodes()
{
  message = "message nr." + counter;

  LoRa.setTxPower(14, RF_PACONFIG_PASELECT_PABOOST);

  LoRa.beginPacket();
  LoRa.println("message nr." + counter++);
  LoRa.endPacket();

  counter++;
}

String receiveMessageFromNode()
{
  // Receive LoRa message
  int packetSize = LoRa.parsePacket();

  if (packetSize)
  {
    String receivedMessage;

    while (LoRa.available())
    {
      receivedMessage += LoRa.read();
    }

    return receivedMessage;
  }

  return "no message received";
}

void LoRaSendTask(void *parameter)
{
  while (true)
  {
    // Core 0 task logic here
    sendMessageToNodes();

    Heltec.display->clear();
    Heltec.display->drawStringMaxWidth(0, 0, 128, "CPU0");
    Heltec.display->drawStringMaxWidth(0, 16, 128, "Sending LoRa package...");
    Heltec.display->drawStringMaxWidth(0, 32, 128, "Message: " + message);
    Heltec.display->display();

    Serial.println("CPU0");
    Serial.println("Message: " + message);

    vTaskDelay(1000 / portTICK_PERIOD_MS); // Delay for 1 second
  }
}

void LoRaReceiveTask(void *parameter)
{
  while (true)
  {
    // Core 1 task logic here
    Heltec.display->clear();
    Heltec.display->drawStringMaxWidth(0, 0, 128, "CPU1");
    Heltec.display->drawStringMaxWidth(0, 16, 128, "Receiving LoRa package: ");
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

  xTaskCreatePinnedToCore(LoRaSendTask, "LoRa Send Task", usStackDepth, pvParameters, uxPriority, pvCreatedTask, 0);
  xTaskCreatePinnedToCore(LoRaReceiveTask, "LoRa Receive Task", usStackDepth, pvParameters, uxPriority, pvCreatedTask, 1);
}

void loop()
{
  // Empty loop as tasks are scheduled by FreeRTOS
  vTaskDelay(1 / portTICK_PERIOD_MS);
}
