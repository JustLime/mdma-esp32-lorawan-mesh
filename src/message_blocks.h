#ifndef MESSAGE_BLOCKS_H
#define MESSAGE_BLOCKS_H

#include "config.h"

struct Header
{
  uint8_t to;
  uint8_t from;
  uint8_t id;
  uint8_t flags;
};

struct Content
{
  String type;
  String value;
};

struct Payload
{
  String topic;
  String senderUuid;
  String messageTimestamp;
  Content content;
};

struct UpdateBlock
{
  uint16_t versionNumber;
  uint16_t numberOfBlocks;
  uint16_t blockIndex;
  std::vector<uint8_t> blockContent;
};

#endif // MESSAGE_BLOCKS_H
