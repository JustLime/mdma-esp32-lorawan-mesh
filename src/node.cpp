#include "node.h"

UUID Node::generateUUID(uint8_t id)
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
  EEPROM.write(0, id);
  Serial.print(F("set nodeId = "));
  Serial.println(id);
}

uint8_t Node::getId()
{
  uint8_t readVal = EEPROM.read(0);

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

  return this->id;
}

void Node::setUuid(String uuid)
{
  this->uuid = uuid;
};

String Node::getUuid()
{
  return this->uuid;
};
