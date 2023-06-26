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
  void updateRoutingTable();
  void getRouteInfoString(char *p, size_t len);
};

MeshNetwork::MeshNetwork()
{
}

MeshNetwork::~MeshNetwork()
{
}

void MeshNetwork::setup()
{
}

#endif // MESH_NETWORK_H