#ifndef NODE_H
#define NODE_H

#include "config.h"

class Node
{
private:
  uint8_t id;

public:
  Node(){};

  UUID generateUUID(uint8_t timestamp);
};

#endif // NODE_H