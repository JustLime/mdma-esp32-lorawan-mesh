/*
 * See here: https://github.com/HelTecAutomation/Heltec_ESP32/blob/master/examples/LoRa/LoRaMultipleCommunication/LoRaMultipleCommunication.ino
 */

#include "heltec.h"

#define BAND 868E6 // you can set band here directly,e.g. 868E6,915E6

String outgoing; // outgoing message

byte localAddress = 0xBB; // address of this device
byte destination = 0xFD;  // destination to send to

byte msgCount = 0;     // count of outgoing messages
long lastSendTime = 0; // last send time
int interval = 1000;   // interval between sends

void sendMessage(String outgoing)
{
  LoRa.beginPacket();            // start packet
  LoRa.write(destination);       // add destination address
  LoRa.write(localAddress);      // add sender address
  LoRa.write(msgCount);          // add message ID
  LoRa.write(outgoing.length()); // add payload length
  LoRa.print(outgoing);          // add payload
  LoRa.endPacket();              // finish packet and send it
  msgCount++;                    // increment message ID
}

void onReceive(int packetSize)
{
  if (packetSize == 0)
    return; // if there's no packet, return

  // read packet header bytes:
  int recipient = LoRa.read();       // recipient address
  byte sender = LoRa.read();         // sender address
  byte incomingMsgId = LoRa.read();  // incoming msg ID
  byte incomingLength = LoRa.read(); // incoming msg length

  String incoming = "";

  while (LoRa.available())
  {
    incoming += (char)LoRa.read();
  }

  if (incomingLength != incoming.length())
  { // check length for error
    Serial.println("error: message length does not match length");
    return; // skip rest of function
  }

  // if message is for this device, or broadcast, print details:
  Serial.println("Received from: 0x" + String(sender, HEX));
  Serial.println("Sent to: 0x" + String(recipient, HEX));
  Serial.println("Message ID: " + String(incomingMsgId));
  Serial.println("Message length: " + String(incomingLength));
  Serial.println("Message: " + incoming);
  Serial.println("RSSI: " + String(LoRa.packetRssi()));
  Serial.println("Snr: " + String(LoRa.packetSnr()));
  Serial.println();

  Heltec.display->clear();
  Heltec.display->drawStringMaxWidth(0, 0, 128, "Received from: 0x" + String(sender, HEX));
  Heltec.display->drawStringMaxWidth(0, 20, 128, "Message ID: " + String(incomingMsgId));
  Heltec.display->drawStringMaxWidth(0, 30, 128, "Message: " + incoming);
  Heltec.display->drawStringMaxWidth(0, 40, 128, "RSSI: " + String(LoRa.packetRssi()));
  Heltec.display->display();
}

void setup()
{
  // WIFI Kit series V1 not support Vext control
  Heltec.begin(true, true, true, true, BAND);

  Serial.println("Heltec.LoRa Duplex");

  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  delay(1500);
  Heltec.display->clear();
}

void loop()
{
  if (millis() - lastSendTime > interval)
  {
    String message = "Hello,I'm coming!"; // send a message
    sendMessage(message);
    Serial.println("Sending " + message);
    lastSendTime = millis(); // timestamp the message
    interval = 1000;         // 1 second
  }

  // parse for a packet, and call onReceive with the result:
  onReceive(LoRa.parsePacket());
}
