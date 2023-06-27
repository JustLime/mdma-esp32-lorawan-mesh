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
  Heltec.display->init();

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

// void loop()
// {
//   char data[] = "Hello, receiver!"; // Message data

//   rf95.send((uint8_t *)data, sizeof(data)); // Send the message data
//   rf95.waitPacketSent();

//   Serial.println("Message sent.");

//   delay(5000);
// }

// Testing code for trivial receiving packages

// #include "RH_RF95.h"

// RH_RF95 rf95(LORA_DEFAULT_SS_PIN, LORA_DEFAULT_DIO0_PIN);

// void setup()
// {
//   Serial.begin(MONITOR_SPEED);

//   pinMode(LORA_DEFAULT_RESET_PIN, OUTPUT);
//   digitalWrite(LORA_DEFAULT_RESET_PIN, HIGH);

//   if (!rf95.init())
//   {
//     Serial.println("LoRa initialization failed!");
//     while (1)
//       ;
//   }

//   rf95.setFrequency(LORA_FREQUENCY);
//   rf95.setTxPower(TX_POWER, false);
// }

void loop()
{
  if (rf95.available())
  {
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
    int8_t rssi = rf95.lastRssi();
    int8_t headerId = rf95.headerId();
    int8_t headerFrom = rf95.headerFrom();
    int8_t headerTo = rf95.headerTo();
    int8_t headerFlags = rf95.headerFlags();

    if (rf95.recv(buf, &len))
    {
      // Output the received message byte by byte
      Serial.print("Received message: ");
      for (int i = 0; i < len; i++)
      {
        Serial.print(buf[i], HEX);
        Serial.print(" ");
      }
      Serial.println();

      Message message;
      Payload payload;
      Content content;

      payload.topic = "v1/backend/measurements/";
      payload.messageTimestamp = "1000000000";
      content.type = "signal-strength";
      content.value = "-53";
      payload.content = content;
      payload.uuid = "0cd1852e-196b-4e2a-a398-6ae835d0caee";
      message.setPayload(payload);

      Display display;
      display.showMessageOnDisplay("RSSI: " + (String)rssi + " dBm");

      Node node;
      UUID uuid = node.generateUUID(payload.messageTimestamp.toInt());
      String uuidString = uuid.toCharArray();
      Serial.println("UUID: " + uuidString);

      // Output the header and message data separately
      Serial.print("Header ID: ");
      Serial.println(headerId);
      Serial.print("Header From: ");
      Serial.println(headerFrom);
      Serial.print("Header To: ");
      Serial.println(headerTo);
      Serial.print("Header Flags: ");
      Serial.println(headerFlags);
      Serial.print("Received message: ");
      for (int i = 0; i < len - 1; i++)
      {
        Serial.print((char)buf[i]);
      }
      Serial.println();

      // Output the RSSI value of the received message
      Serial.print("RSSI: ");
      Serial.print(rssi);
      Serial.println(" dBm");
    }
    else
    {
      Serial.println("Receive failed.");
    }
  }
}
