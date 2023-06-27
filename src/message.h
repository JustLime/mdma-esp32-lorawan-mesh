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
  String uuid;
  String messageTimestamp;
  Content content;
};

class Message
{
private:
  Header header;
  Payload payload;

public:
  Message();
  Message(Header header, Payload payload);

  void setHeader(Header header);
  Header getHeader();
  void setPayload(Payload payload);
  Payload getPayload();
  String getSerializedMessage();
};

#endif // MESSAGE_H
