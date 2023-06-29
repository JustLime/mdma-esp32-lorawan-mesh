#include "config.h"

Display display;
Node node;

uint8_t routes[N_NODES]; // full routing table for mesh
int16_t rssi[N_NODES];   // signal strength info
char buf[MAX_MESSAGE_SIZE];

uint8_t nodeId;
String uuid;

void MeshNetwork::setup()
{
  Heltec.display->init();
  Serial.begin(MONITOR_SPEED);

  pinMode(LORA_DEFAULT_RESET_PIN, OUTPUT);
  digitalWrite(LORA_DEFAULT_RESET_PIN, HIGH);

  manager = new RHMesh(rf95, 1);

  rf95.setFrequency(LORA_FREQUENCY);
  rf95.setTxPower(TX_POWER, false);
  rf95.setSpreadingFactor(SPREADING_FACTOR);
  rf95.setCADTimeout(CAD_TIMEOUT);

  // See here: https://www.airspayce.com/mikem/arduino/RadioHead/classRH__RF95.html#ab9605810c11c025758ea91b2813666e3
  if (!rf95.setModemConfig(RH_RF95::Bw125Cr45Sf128))
  {
    Serial.println(ErrorMessage::MODEM_CONFIG_FAILED);
    display.showMessageOnDisplay(ErrorMessage::MODEM_CONFIG_FAILED);
  }
  Serial.println("RF95 ready");
  display.showMessageOnDisplay("RF95 ready");

  Serial.print(F("initializing node "));

  node.setId(NODE_ID);

  uuid = node.generateUuid(NODE_ID).toCharArray();
  node.setUuid(uuid);

  if (!manager->init())
  {
    Serial.println("Mesh init failed");
    display.showMessageOnDisplay("Mesh init failed");
  }
  else
  {
    Serial.println("Mesh init done");
    display.showMessageOnDisplay("Mesh init done");

    display.showQRCode(uuid);
  }
}

void MeshNetwork::loop()
{
  for (uint8_t n = 1; n <= N_NODES; n++)
  {
    if (n == nodeId)
      continue; // self

    // updateRoutingTable();
    // getRouteInfoString(buf, MAX_MESSAGE_SIZE);

    Serial.print(F("->"));
    Serial.print(n);
    Serial.print(F(" :"));
    Serial.print(buf);

    // send an acknowledged message to the target node
    Message signalStrength = Message("v1/backend/measurements/",
                                     uuid,
                                     "0",
                                     "signal-strength",
                                     node.generateUuid(n).toCharArray() + (String) "/" + (String)rf95.lastRssi());
    const char *c_str_message = signalStrength.getSerializedMessage().c_str();
    uint8_t sentMessage = manager->sendtoWait((uint8_t *)c_str_message, strlen(c_str_message), RH_BROADCAST_ADDRESS);
    if (sentMessage != RH_ROUTER_ERROR_NONE)
    {
      Serial.println();
      Serial.print(F(" ! "));
      Serial.println(getErrorString(sentMessage));
    }
    else
    {
      Serial.println(F(" OK"));

      digitalWrite(LED, HIGH);
      delay(500);
      digitalWrite(LED, LOW);

      // we received an acknowledgement from the next hop for the node we tried to send to.
      // RHRouter::RoutingTableEntry *route = manager->getRouteTo(n);
      // FIXME: Microcontroller is crashing, because route is always null. Perhaps the library has a bug.
      // if (route->next_hop != 0)
      // {
      //   rssi[route->next_hop - 1] = rf95.lastRssi();
      // }
    }
    // if (nodeId == 1)
    //   printNodeInfo(nodeId, buf); // debugging

    // listen for incoming messages. Wait a random amount of time before we transmit
    // again to the next node

    unsigned long nextTransmit = millis() + TRANSMIT_INTERVAL;
    while (nextTransmit > millis())
    {
      int waitTime = nextTransmit - millis();
      uint8_t len = sizeof(buf);
      uint8_t from;

      if (manager->recvfromAck((uint8_t *)buf, &len, &from))
      {
        buf[len] = '\0'; // null terminate string
        Serial.print(from);
        Serial.print(F("->"));
        Serial.print(F(" :"));
        Serial.println(buf);
        // if (nodeId == 1)
        //   printNodeInfo(from, buf); // debugging

        digitalWrite(LED, HIGH);
        delay(200);
        digitalWrite(LED, LOW);
        delay(200);
        digitalWrite(LED, HIGH);
        delay(200);
        digitalWrite(LED, LOW);
        delay(200);
        digitalWrite(LED, HIGH);
        delay(200);
        digitalWrite(LED, LOW);
        delay(200);

        Serial.println("RSSI: " + (String)rf95.lastRssi());

        manager->sendtoWait((uint8_t *)buf, strlen(buf), RH_BROADCAST_ADDRESS);

        // we received data from node 'from', but it may have actually come from an intermediate node
        // RHRouter::RoutingTableEntry *route = manager->getRouteTo(from);
        // if (route->next_hop != 0)
        // FIXME: Microcontroller is crashing, because route is always null. Perhaps the library has a bug.
        // {
        //   rssi[route->next_hop - 1] = rf95.lastRssi();
        // }
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

const String MeshNetwork::getErrorString(uint8_t error)
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

void MeshNetwork::updateRoutingTable()
{
  for (uint8_t n = 1; n <= N_NODES; n++)
  {
    RHRouter::RoutingTableEntry *route = manager->getRouteTo(n);
    // FIXME: Microcontroller is crashing, because route is always null. Perhaps the library has a bug.
    if (n == nodeId)
    {
      routes[n - 1] = 255; // self
    }
    else
    {
      routes[n - 1] = route->next_hop;
      if (routes[n - 1] == 0)
      {
        // if we have no route to the node, reset the received signal strength
        rssi[n - 1] = 0;
      }
    }
  }
}