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
