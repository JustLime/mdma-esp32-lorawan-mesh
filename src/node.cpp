#include "node.h"

UUID Node::generateUuid(uint8_t id)
{
  UUID uuid;
  uuid.seed(id);
  uuid.generate();

  return uuid;
}

void Node::setId(uint8_t id)
{
  Serial.println("setting nodeId...");

  this->id = id;
  EEPROM.put(0, id);
  Serial.print(F("set nodeId = "));
  Serial.println(id);
}

uint8_t Node::getId()
{
  uint8_t readVal;
  EEPROM.get(0, readVal);

  Serial.print(F("read nodeId: "));
  Serial.println(readVal);

  if (id != readVal)
  {
    Serial.println(F("*** FAIL ***"));
  }
  else
  {
    Serial.println(F("SUCCESS"));
  }

  return readVal;
}

void Node::setUuid(String uuid)
{
  this->uuid = uuid;
};

String Node::getUuid()
{
  return this->uuid;
};
