#include "node.h"

UUID Node::generateUUID(uint8_t timestamp)
{
  UUID uuid;
  uuid.seed(timestamp);
  uuid.generate();

  return uuid;
}
