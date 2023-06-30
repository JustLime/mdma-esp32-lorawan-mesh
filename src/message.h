#ifndef MESSAGE_H
#define MESSAGE_H

#include "config.h"

/**
 * @file message.h
 * @authors Christian Deme, Leon Trunk, Rudolf Zitlau
 * @brief Defines a LoRa message used in the mesh network.
 * @version 0.1
 * @date 2023-06-23
 *
 * @copyright Copyright (c) 2023
 */

class Message
{
private:
  Header header;
  Payload payload;

public:
  Message();
  Message(String topic, String senderUuid, String messageTimestamp, String type, String value);
  Message(Header header, Payload payload);

  void setHeader(Header header);
  Header getHeader();
  void setPayload(Payload payload);
  Payload getPayload();
  String getSerializedMessage();
};

UpdateBlock parseUpdateBlock(const uint8_t *receivedPacket, size_t size);

void serializeUpdateBlock(uint8_t *updatePacketLocation, size_t reservedSize, UpdateBlock updateBlock);

UpdateBlock createUpdateBlock(uint16_t versionNumber, uint16_t numberOfBlocks, uint16_t blockIndex, std::vector<uint8_t> &blockContent);

#endif // MESSAGE_H
