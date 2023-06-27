#include "config.h"

RH_RF95 rf95(LLG_CS, LLG_DI0);
uint8_t nodeId;
RHMesh *manager;
Display display;
MeshNetwork network;

int16_t rssi[N_NODES]; // signal strength info

void setup()
{
  network.setup();

  network.initRoutes();
}

void loop()
{
  network.loop();
}
