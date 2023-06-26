#ifndef MESSAGE_H
#define MESSAGE_H

#include "config.h"

/**
 * @file message.h
 * @author Christian Deme, Leon Trunk, Rudolf Zitlau
 * @brief Defines a LoRa message used in the mesh network.
 * @version 0.1
 * @date 2023-06-23
 *
 * @copyright Copyright (c) 2023
 *
 */

class Message
{
private:
  uint8_t body;

public:
  Message();
  ~Message();

  uint8_t getBody();
  void setBody(uint8_t body);
  bool sendMessage();
  bool receiveMessage();
};

#endif // MESSAGE_H
