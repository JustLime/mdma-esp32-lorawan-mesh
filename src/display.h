#ifndef DISPLAY_H
#define DISPLAY_H

#include "config.h"

class Display
{
public:
  Display(/* args */);
  ~Display();

  void showMessageOnDisplay(char message[]);
  void showQRCode(uint8_t uuid);
};

#endif // DISPLAY_H