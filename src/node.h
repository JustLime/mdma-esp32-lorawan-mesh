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

public:
  Node(){};

  void setId(uint8_t id);
  uint8_t getId();
  void setUuid(String uuid);
  String getUuid();
  UUID generateUuid(uint8_t id);
};

#endif // NODE_H