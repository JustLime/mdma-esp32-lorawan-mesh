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

#include "display.h"
#include "error_message.h"

// Pin Definitions for Heltec WiFi Lora 32 V2
#define LLG_SCK 5
#define LLG_MISO 19
#define LLG_MOSI 27
#define LLG_CS 18 // Chip select pin
#define LLG_RST 16
#define LLG_DI0 26 // Interrupt pin on DI0
#define LLG_DI1 35
#define LLG_DI2 34

// Display
#define SCREEN_WIDTH 128

// Mesh Network
#define N_NODES 2
#define TRANSMIT_INTERVAL 1000
#define INITIAL_NODE_ID 255
#define GATEWAY_ADDRESS 1

// LoRa
#define MAX_MESSAGE_SIZE 244
#define SPREADING_FACTOR 7
#define LORA_FREQUENCY 868.0 // 868MHz for Europe
#define TX_POWER 13
#define CAD_TIMEOUT 500

#endif // CONFIG_H