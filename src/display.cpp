#include "display.h"

void Display::showMessageOnDisplay(char *message)
{
  Heltec.display->clear();
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawStringMaxWidth(0, 0, SCREEN_WIDTH, message);
  Heltec.display->display();
}

void Display::showMessageOnDisplay(const char *message)
{
  Heltec.display->clear();
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawStringMaxWidth(0, 0, SCREEN_WIDTH, message);
  Heltec.display->display();
}

void Display::showQRCode(uint8_t uuid)
{
  QRcodeOled qrcode(Heltec.display);

  qrcode.init();
  qrcode.create("UUID: " + uuid);
}