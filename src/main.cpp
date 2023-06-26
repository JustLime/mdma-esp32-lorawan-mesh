/**
 * @file main.cpp
 * @author Christian Deme, Leon Trunk, Rudolf Zitlau
 * @brief Implementation of a LoRa mesh network using RadioHead written for Heltec WiFi LoRa 32 V2.
 * Taken inspiration from: https://github.com/nootropicdesign/lora-mesh/tree/master
 * @version 0.1
 * @date 2023-06-16
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "config.h"

RH_RF95 rf95(LLG_CS, LLG_DI0);
RHMesh *manager;
Display display;
MeshNetwork network;

uint8_t nodeId;
int16_t rssi[N_NODES]; // signal strength info
char buf[MAX_MESSAGE_SIZE];

void setup()
{
  network.setup();

  nodeId = 1;

  Serial.print(F("initializing node "));

  manager = new RHMesh(rf95, nodeId);

  if (!manager->init())
  {
    Serial.println(" init failed");
    display.showMessageOnDisplay(" init failed");
  }
  else
  {
    Serial.println(" done");
    display.showMessageOnDisplay(" done");
  }

  network.initRoutes();
}

const __FlashStringHelper *getErrorString(uint8_t error)
{
  switch (error)
  {
  case 1:
    return F("invalid length");
    break;
  case 2:
    return F("no route");
    break;
  case 3:
    return F("timeout");
    break;
  case 4:
    return F("no reply");
    break;
  case 5:
    return F("unable to deliver");
    break;
  }
  return F("unknown");
}

void printNodeInfo(uint8_t node, char *s)
{
  Serial.print(F("node: "));
  Serial.print(F("{"));
  Serial.print(F("\""));
  Serial.print(node);
  Serial.print(F("\""));
  Serial.print(F(": "));
  Serial.print(s);
  Serial.println(F("}"));
}

void loop()
{
  for (uint8_t n = 1; n <= N_NODES; n++)
  {
    if (n == nodeId)
      continue; // self

    network.updateRoutingTable();
    network.getRouteInfoString(buf, RH_MESH_MAX_MESSAGE_LEN);

    Serial.print(F("->"));
    Serial.print(n);
    Serial.print(F(" :"));
    Serial.print(buf);
    // send an acknowledged message to the target node
    uint8_t error = manager->sendtoWait((uint8_t *)buf, strlen(buf), n);
    if (error != RH_ROUTER_ERROR_NONE)
    {
      Serial.println();
      Serial.print(F(" ! "));
      Serial.println(getErrorString(error));
    }
    else
    {
      Serial.println(F(" OK"));
      // we received an acknowledgement from the next hop for the node we tried to send to.
      RHRouter::RoutingTableEntry *route = manager->getRouteTo(n);
      if (route->next_hop != 0)
      {
        rssi[route->next_hop - 1] = rf95.lastRssi();
      }
    }
    if (nodeId == 1)
      printNodeInfo(nodeId, buf); // debugging

    // listen for incoming messages. Wait a random amount of time before we transmit
    // again to the next node
    unsigned long nextTransmit = millis() + TRANSMIT_INTERVAL;
    while (nextTransmit > millis())
    {
      int waitTime = nextTransmit - millis();
      uint8_t len = sizeof(buf);
      uint8_t from;
      if (manager->recvfromAckTimeout((uint8_t *)buf, &len, waitTime, &from))
      {
        buf[len] = '\0'; // null terminate string
        Serial.print(from);
        Serial.print(F("->"));
        Serial.print(F(" :"));
        Serial.println(buf);
        if (nodeId == 1)
          printNodeInfo(from, buf); // debugging

        // we received data from node 'from', but it may have actually come from an intermediate node
        RHRouter::RoutingTableEntry *route = manager->getRouteTo(from);
        if (route->next_hop != 0)
        {
          rssi[route->next_hop - 1] = rf95.lastRssi();
        }
      }
    }
  }
}
