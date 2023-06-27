#ifndef NODE_H
#define NODE_H

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
  UUID generateUUID(uint8_t id);
};

#endif // NODE_H