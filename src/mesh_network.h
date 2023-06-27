#ifndef MESH_NETWORK_H
#define MESH_NETWORK_H

/**
 * @file mesh_network.h
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