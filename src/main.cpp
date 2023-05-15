#include "heltec.h"


void setup()
{
  Serial.begin(115200);
  Heltec.begin(true,false,true);
}

void loop() {}
