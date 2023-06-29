#ifndef DISPLAY_H
#define DISPLAY_H

/**
 * @file display.h
 * @author Christian Deme, Leon Trunk, Rudolf Zitlau
 * @brief Defines all the necessary functions to show information on the OLED display.
 * @version 0.1
 * @date 2023-06-23
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "config.h"

class Display
{
public:
  Display(){};

  void showMessageOnDisplay(char *message);
  void showMessageOnDisplay(const char *message);
  void showMessageOnDisplay(const String message);
  void showQRCode(String uuid);
};

#endif // DISPLAY_H