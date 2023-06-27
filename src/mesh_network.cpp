#include "config.h"

Display display;

uint8_t routes[N_NODES]; // full routing table for mesh
int16_t rssi[N_NODES];   // signal strength info
char buf[MAX_MESSAGE_SIZE];
uint8_t nodeId = 1;

void MeshNetwork::setup()
{
  Heltec.display->init();
  Serial.begin(MONITOR_SPEED);

  rf95.setFrequency(LORA_FREQUENCY);
  rf95.setTxPower(TX_POWER, false);
  rf95.setSpreadingFactor(SPREADING_FACTOR);
  rf95.setCADTimeout(CAD_TIMEOUT);

  if (!rf95.setModemConfig(RH_RF95::Bw125Cr45Sf128))
  {
    Serial.println(F(ErrorMessage::MODEM_CONFIG_FAILED));
    display.showMessageOnDisplay(ErrorMessage::MODEM_CONFIG_FAILED);
  }
  Serial.println("RF95 ready");
  display.showMessageOnDisplay("RF95 ready");

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
}

void MeshNetwork::loop()
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

void MeshNetwork::getRouteInfoString(char *p, size_t len)
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

void MeshNetwork::initRoutes()
{
  for (uint8_t n = 1; n <= N_NODES; n++)
  {
    routes[n - 1] = 0;
    rssi[n - 1] = 0;
  }
}

void MeshNetwork::printNodeInfo(uint8_t node, char *s)
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

const __FlashStringHelper *MeshNetwork::getErrorString(uint8_t error)
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