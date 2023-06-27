#ifndef DISPLAY_H
#define DISPLAY_H

#include "config.h"

class Display
{
public:
  Display(){};

  void showMessageOnDisplay(char *message);
  void showMessageOnDisplay(const char *message);
  void showQRCode(uint8_t uuid);
};

#endif // DISPLAY_H