#include "message.h"

Message::Message() {}

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

String Message::serializeMessage()
{
  StaticJsonDocument<MAX_MESSAGE_SIZE> doc;
  doc["topic"] = this->getPayload().topic;
  doc["uuid"] = this->getPayload().uuid;
  doc["messageTimestamp"] = this->getPayload().messageTimestamp;
  doc["content"]["type"] = this->getPayload().content.type;
  doc["content"]["value"] = this->getPayload().content.value;

  String jsonString;
  serializeJson(doc, jsonString);

  return jsonString;
}
