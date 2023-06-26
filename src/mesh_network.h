#ifndef MESH_NETWORK_H
#define MESH_NETWORK_H

#include "config.h"

class MeshNetwork
{
private:
  RH_RF95 rf95;
  RHMesh *manager;

public:
  MeshNetwork();

  void setup();
  void loop();
  void initRoutes();
  void updateRoutingTable();
  void getRouteInfoString(char *p, size_t len);
  void printNodeInfo(uint8_t node, char *s);
  const __FlashStringHelper *getErrorString(uint8_t error);
};

#endif // MESH_NETWORK_H