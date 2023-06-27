// Production implementation

#include "config.h"

// RH_RF95 rf95(LORA_DEFAULT_SS_PIN, LORA_DEFAULT_DIO0_PIN);
// MeshNetwork network;

// void setup()
// {
//   network.setup();

//   network.initRoutes();
// }

// void loop()
// {
//   network.loop();
// }

// Testing code for trivial sending packages every 5 seconds

#include "RH_RF95.h"

RH_RF95 rf95(LORA_DEFAULT_SS_PIN, LORA_DEFAULT_DIO0_PIN);

void setup()
{
  Serial.begin(MONITOR_SPEED);

  pinMode(LORA_DEFAULT_RESET_PIN, OUTPUT);
  digitalWrite(LORA_DEFAULT_RESET_PIN, HIGH);

  if (!rf95.init())
  {
    Serial.println("LoRa initialization failed!");
    while (1)
      ;
  }

  rf95.setFrequency(LORA_FREQUENCY);
  rf95.setTxPower(TX_POWER, false);
}

void loop()
{
  const char *message = "Hello, world!";

  rf95.send((uint8_t *)message, strlen(message));
  rf95.waitPacketSent();

  Serial.print("Message sent: ");
  Serial.println(message);

  delay(3000); // Wait for 3 seconds before sending the next message
}
