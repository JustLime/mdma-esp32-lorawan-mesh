#include "message.h"

Message::Message() {}

Message::Message(String topic, String senderUuid, String messageTimestamp, String type, String value)
{
  Message message;
  Payload payload;
  Content content;

  payload.topic = topic;
  payload.senderUuid = senderUuid;
  payload.messageTimestamp = messageTimestamp;
  content.type = type;
  content.value = value;
  payload.content = content;

  this->payload = payload;
}

Message::Message(Header header, Payload payload)
{
  this->header = header;
  this->payload = payload;
}

void Message::setHeader(Header header)
{
  this->header = header;
}

Header Message::getHeader()
{
  return this->header;
}

void Message::setPayload(Payload payload)
{
  this->payload = payload;
}

Payload Message::getPayload()
{
  return this->payload;
}

String Message::getSerializedMessage()
{
  StaticJsonDocument<MAX_MESSAGE_SIZE> doc;
  doc["topic"] = this->getPayload().topic;
  doc["sender_uuid"] = this->getPayload().senderUuid;
  doc["messageTimestamp"] = this->getPayload().messageTimestamp;
  doc["content"]["type"] = this->getPayload().content.type;
  doc["content"]["value"] = this->getPayload().content.value;

  String jsonString;
  serializeJson(doc, jsonString);

  return jsonString;
}

UpdateBlock createUpdateBlock(uint16_t versionNumber, uint16_t numberOfBlocks, uint16_t blockIndex, std::vector<uint8_t> &blockContent)
{
  UpdateBlock block;
  block.versionNumber = versionNumber;
  block.numberOfBlocks = numberOfBlocks;
  block.blockIndex = blockIndex;
  block.blockContent = blockContent;

  return block;
}

UpdateBlock parseUpdateBlock(const uint8_t *receivedPacket, size_t size)
{
  if (size < 7)
  {
    throw std::invalid_argument("Packet too small to be valid!");
  }

  if (receivedPacket[0] != 0xFF)
  {
    throw std::invalid_argument("Malformed Packet!");
  }
  UpdateBlock block;
  block.versionNumber = (receivedPacket[1] << 8) | receivedPacket[2];
  block.numberOfBlocks = (receivedPacket[3] << 8) | receivedPacket[4];
  block.blockIndex = (receivedPacket[5] << 8) | receivedPacket[6];
  block.blockContent.assign(receivedPacket + 7, receivedPacket + size);

  return block;
}

void serializeUpdateBlock(uint8_t *updatePacketLocation, size_t reservedSize, UpdateBlock updateBlock)
{
  if (reservedSize < updateBlock.blockContent.size() + 7)
  {
    throw std::invalid_argument("Insufficient reserved size for the block content!");
  }

  updatePacketLocation[0] = 0xFF;
  updatePacketLocation[1] = updateBlock.versionNumber >> 8;
  updatePacketLocation[2] = updateBlock.versionNumber;
  updatePacketLocation[3] = updateBlock.numberOfBlocks >> 8;
  updatePacketLocation[4] = updateBlock.numberOfBlocks;
  updatePacketLocation[5] = updateBlock.blockIndex >> 8;
  updatePacketLocation[6] = updateBlock.blockIndex;
  std::memcpy(updatePacketLocation + 7, updateBlock.blockContent.data(), updateBlock.blockContent.size());
}
