#ifndef NODE_H
#define NODE_H

/**
 * @file node.h
 * @author Christian Deme, Leon Trunk, Rudolf Zitlau
 * @brief Defines a node at its functions used in a mesh network.
 * @version 0.1
 * @date 2023-06-23
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "config.h"

class Node
{
private:
  uint8_t id;
  String uuid;
  RHMesh *manager;

public:
  Node(){};
  Node(RHMesh *manager)
  {
    this->manager = manager;
  };

  void setId(uint8_t id);
  uint8_t getId();
  void setUuid(String uuid);
  String getUuid();
  uint8_t sendMessage(RHMesh *manager, Message message, uint8_t to);
  void handleUpdateMessage(UpdateBlock updateBlock, RHMesh *manager);
  void requestMissingPacket(uint16_t blockIndex);
  bool checkIfPreviouslyReceived(uint16_t version, uint16_t blockIndex);
  uint32_t makeKey(uint16_t version, uint16_t blockIndex);
  void broadcastUpdateBlock(UpdateBlock updateBlock, RHMesh *manager);
  UUID generateUuid(uint8_t id);
};

#endif // NODE_H