#ifndef CONFIG_H
#define CONFIG_H

/**
 * @file config.h
 * @author Christian Deme, Leon Trunk, Rudolf Zitlau
 * @brief Configuration file defining all the necessary data for the program.
 * @version 0.1
 * @date 2023-06-23
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "RH_RF95.h"
#include "RHMesh.h"
#include "heltec.h"
#include <qrcodeoled.h>
#include "ArduinoJson.h"
#include "UUID.h"
#include "EEPROM.h"

#include "display.h"
#include "mesh_network.h"
#include "error_message.h"
#include "message.h"
#include "node.h"

// All further pin Definitions for Heltec WiFi Lora 32 V2

// SPI clock pin.
#define LORA_SCK 5
// SPI data input pin.
#define LORA_MISO 19
// SPI data output pin.
#define LORA_MOSI 27
// Interrupt pin for DI1.
#define LORA_DI1 35
// Interrupt pin for DI2.
#define LORA_DI2 34

// Specific settings for ESP32 devices

// Serial monitor speed used for this device.
#define MONITOR_SPEED 115200
// Size of the EEPROM (Electrically Erasable Programmable Read Only Memory).
#define EEPROM_SIZE 4

// Display

// Screen width of the OLED display.
#define SCREEN_WIDTH 128
// Screen height of the OLED display.
#define SCREEN_HEIGHT 64

// Mesh Network

// Number of nodes in this mesh network.
#define N_NODES 3
// Interval of sending messages in milliseconds.
#define TRANSMIT_INTERVAL 3000
// Initial node ID for a node, should be overwritten by the right ID.
#define INITIAL_NODE_ID 255
// Node ID of the gateway ESP32 device.
#define GATEWAY_ADDRESS 0

// LoRa
#define MAX_MESSAGE_SIZE 244 /// Maximum message size of 244 bytes.
/// Spreading factor of the transmission.
/// The higher the spreading factor the slower is the transmission speed but more devices could be reached.
/// Minimium is 7, maximum is 12.
#define SPREADING_FACTOR 10
// Default LoRa frequency of 868MHz for Europe.
#define LORA_FREQUENCY 868.0
/// Transmission power used for transmitting messages over LoRa radios in dBm.
/// Max. allowed in Europe is 14.
#define TX_POWER 14
// Channel Activity Detection timeout in milliseconds.
#define CAD_TIMEOUT 500

#endif // CONFIG_H