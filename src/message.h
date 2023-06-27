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

struct Message
{
  uint8_t preamble;
  uint8_t header; // TO, FROM, ID, FLAGS
  uint8_t payload;
};

#endif // MESSAGE_H
