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

#include "heltec.h"
#include "RH_RF95.h"
#include "RHMesh.h"

#include "error_message.h"

// Pin Definitions
#define LLG_SCK 5
#define LLG_MISO 19
#define LLG_MOSI 27
#define LLG_CS 18 // Chip select pin
#define LLG_RST 16
#define LLG_DI0 26 // Interrupt pin on DI0
#define LLG_DI1 35
#define LLG_DI2 34

#define MAX_MESSAGE_SIZE 244
#define N_NODES 2
#define TRANSMIT_INTERVAL 1000

RH_RF95 rf95(LLG_CS, LLG_DI0);
RHMesh *manager;

uint8_t nodeId;
uint8_t routes[N_NODES]; // full routing table for mesh
int16_t rssi[N_NODES];   // signal strength info
char buf[RH_MESH_MAX_MESSAGE_LEN];

void showMessageOnDisplay(char message[])
{
  Heltec.display->clear();
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawStringMaxWidth(0, 0, 128, message);
  Heltec.display->display();
}

void setup()
{
  Heltec.display->init();
  Serial.begin(115200);

  rf95.setFrequency(868.0);
  rf95.setTxPower(13, false);
  rf95.setSpreadingFactor(7);
  rf95.setCADTimeout(500);

  nodeId = 1;

  Serial.print(F("initializing node "));

  manager = new RHMesh(rf95, nodeId);

  if (!manager->init())
  {
    Serial.println(" init failed");
    showMessageOnDisplay(" init failed");
  }
  else
  {
    Serial.println(" done");
    showMessageOnDisplay(" done");
  }

  if (!rf95.setModemConfig(RH_RF95::Bw125Cr45Sf128))
  {
    Serial.println(F(ErrorMessage::MODEM_CONFIG_FAILED));
    showMessageOnDisplay(ErrorMessage::MODEM_CONFIG_FAILED);
  }
  Serial.println("RF95 ready");
  showMessageOnDisplay("RF95 ready");

  for (uint8_t n = 1; n <= N_NODES; n++)
  {
    routes[n - 1] = 0;
    rssi[n - 1] = 0;
  }
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

void updateRoutingTable()
{
  for (uint8_t n = 1; n <= N_NODES; n++)
  {
    RHRouter::RoutingTableEntry *route = manager->getRouteTo(n);
    if (n == nodeId)
    {
      routes[n - 1] = 255; // self
    }
    else
    {
      // routes[n - 1] = route->next_hop; // TODO: Keeps resetting, when nodeId is 0, NULL or invalid
      if (routes[n - 1] == 0)
      {
        // if we have no route to the node, reset the received signal strength
        rssi[n - 1] = 0;
      }
    }
  }
}

// Create a JSON string with the routing info to each node
void getRouteInfoString(char *p, size_t len)
{
  p[0] = '\0';
  strcat(p, "[");
  for (uint8_t n = 1; n <= N_NODES; n++)
  {
    strcat(p, "{\"n\":");
    sprintf(p + strlen(p), "%d", routes[n - 1]);
    strcat(p, ",");
    strcat(p, "\"r\":");
    sprintf(p + strlen(p), "%d", rssi[n - 1]);
    strcat(p, "}");
    if (n < N_NODES)
    {
      strcat(p, ",");
    }
  }
  strcat(p, "]");
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

    updateRoutingTable();
    getRouteInfoString(buf, RH_MESH_MAX_MESSAGE_LEN);

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
