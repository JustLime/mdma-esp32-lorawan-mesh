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

#include "display.h"
#include "mesh_network.h"
#include "error_message.h"

// Pin Definitions for Heltec WiFi Lora 32 V2
#define LLG_SCK 5   // SPI clock pin
#define LLG_MISO 19 // SPI data input pin
#define LLG_MOSI 27 // SPI data output pin
#define LLG_CS 18   // Chip select pin
#define LLG_RST 16  // Reset pin
#define LLG_DI0 26  // Interrupt pin on DI0
#define LLG_DI1 35  // Interrupt pin for DI1
#define LLG_DI2 34  // Interrupt pin for DI2

// Specific settings for ESP32 devices
#define MONITOR_SPEED 115200 // Serial monitor speed used for this device.

// Display
#define SCREEN_WIDTH 128 // Screen width of the OLED display.
#define SCREEN_HEIGHT 64 // Screen height of the OLED display.

// Mesh Network
#define N_NODES 2              // Number of nodes in this mesh network.
#define TRANSMIT_INTERVAL 1000 // Interval of sending messages in milliseconds.
#define INITIAL_NODE_ID 255    // Initial node ID for a node, should be overwritten by the right ID.
#define GATEWAY_ADDRESS 1      // Node ID of the gateway ESP32 device.

// LoRa
#define MAX_MESSAGE_SIZE 244 // Maximum message size of 244 bytes.
#define SPREADING_FACTOR 7   // Spreading factor of the transmission, the higher the spreading factor the slower is the transmission speed but more devices could be reached.
#define LORA_FREQUENCY 868.0 // Default LoRa frequency of 868MHz for Europe.
#define TX_POWER 13          // Transmission power used for transmitting messages over LoRa radios, max. in Europe should be 14
#define CAD_TIMEOUT 500      // Channel Activity Detection timeout in milliseconds

#endif // CONFIG_H