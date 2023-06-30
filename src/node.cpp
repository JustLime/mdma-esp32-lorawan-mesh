#include "node.h"

OTAUpdate otaUpdate;
std::unordered_map<uint32_t, bool> receivedPackets;

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

uint8_t Node::sendMessage(RHMesh *manager, Message message, uint8_t to)
{
  const char *c_str_message = message.getSerializedMessage().c_str();

  return manager->sendtoWait((uint8_t *)c_str_message, strlen(c_str_message), to);
}

void Node::requestMissingPacket(uint16_t blockIndex)
{
  Message message = Message("v1/updates/missing", uuid, "0", "missingBlockIndex", (String)blockIndex);

  sendMessage(manager, message, GATEWAY_ADDRESS);
}

void Node::handleUpdateMessage(UpdateBlock updateBlock, RHMesh *manager)
{
  uint32_t key = makeKey(updateBlock.versionNumber, updateBlock.blockIndex);
  if (!checkIfPreviouslyReceived(updateBlock.versionNumber, updateBlock.blockIndex))
  {
    receivedPackets[key] = true;
    broadcastUpdateBlock(updateBlock, manager);
  }

  Serial.print("Current version: ");
  Serial.println(CURRENT_VERSION);

  if (updateBlock.blockIndex == 0)
  {
    if (otaUpdate.begin(updateBlock.numberOfBlocks, updateBlock.versionNumber))
      Serial.println("Update begin");
  }

  bool isWritten = otaUpdate.write(updateBlock);

  if (isWritten)
  {
    Serial.println("update is running");
    return;
  }

  if (otaUpdate.getVersion() < updateBlock.versionNumber)
  {
    otaUpdate.abortUpdate();
  }
  else if (otaUpdate.getExpectedBlockIndex() < updateBlock.blockIndex)
  {
    requestMissingPacket(otaUpdate.getExpectedBlockIndex());
  }
}

bool Node::checkIfPreviouslyReceived(uint16_t version, uint16_t blockIndex)
{
  uint32_t key = makeKey(version, blockIndex);
  return receivedPackets.find(key) != receivedPackets.end();
}

uint32_t Node::makeKey(uint16_t version, uint16_t blockIndex)
{
  return (static_cast<uint32_t>(version) << 16) | blockIndex;
}

void Node::broadcastUpdateBlock(UpdateBlock updateBlock, RHMesh *manager)
{
  uint8_t buf[MAX_MESSAGE_SIZE];
  serializeUpdateBlock(buf, MAX_MESSAGE_SIZE, updateBlock);
  bool sent = manager->sendtoWait(buf, MAX_MESSAGE_SIZE, RH_BROADCAST_ADDRESS);
}

UUID Node::generateUuid(uint8_t id)
{
  UUID uuid;
  uuid.seed(id);
  uuid.generate();

  return uuid;
}
