#include "config.h"

Display display;

uint8_t routes[N_NODES]; // full routing table for mesh
int16_t rssi[N_NODES];   // signal strength info

void MeshNetwork::setup()
{
  Heltec.display->init();
  Serial.begin(115200);

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