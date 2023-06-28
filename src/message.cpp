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
