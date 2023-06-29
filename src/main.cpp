#include "heltec.h"
#define BAND 868E6

int counter = 0;
bool receiver = false;
String rssi = "RSSI --";
String packSize = "--";
String packet;

void setup()
{
  Heltec.begin(true, true, true, true, BAND);

  if (receiver)
  {
    Heltec.display->init();
    Heltec.display->flipScreenVertically();
    Heltec.display->setFont(ArialMT_Plain_10);
    delay(1500);
    Heltec.display->clear();

    Heltec.display->drawString(0, 0, "Heltec.LoRa Initial success!");
    Heltec.display->drawString(0, 10, "Wait for incoming data...");
    Heltec.display->display();
    delay(1000);
    // LoRa.onReceive(cbk);
    LoRa.receive();
  }
}
void LoRaData()
{
  Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawString(0, 15, "Received " + packSize + " bytes");
  Heltec.display->drawStringMaxWidth(0, 26, 128, packet);
  Heltec.display->drawString(0, 0, rssi);
  Heltec.display->display();
}

void cbk(int packetSize)
{
  packet = "";
  packSize = String(packetSize, DEC);
  for (int i = 0; i < packetSize; i++)
  {
    packet += (char)LoRa.read();
  }
  rssi = "RSSI " + String(LoRa.packetRssi(), DEC);
  LoRaData();
}

void loop()
{
  if (receiver)
  {
    int packetSize = LoRa.parsePacket();
    if (packetSize)
    {
      cbk(packetSize);
    }
    delay(10);
  }
  else
  {

    Serial.print("Sending packet: ");
    Serial.println(counter);
    // send packet
    LoRa.beginPacket();
    /*
     * LoRa.setTxPower(txPower,RFOUT_pin);
     * txPower -- 0 ~ 20
     * RFOUT_pin could be RF_PACONFIG_PASELECT_PABOOST or RF_PACONFIG_PASELECT_RFO
     *   - RF_PACONFIG_PASELECT_PABOOST -- LoRa single output via PABOOST, maximum output 20dBm
     *   - RF_PACONFIG_PASELECT_RFO     -- LoRa single output via RFO_HF / RFO_LF, maximum output 14dBm
     */
    LoRa.setTxPower(14, RF_PACONFIG_PASELECT_PABOOST);
    LoRa.print("hello ");
    LoRa.print(counter);
    LoRa.endPacket();

    counter++;
    digitalWrite(25, HIGH);
    delay(1000);
    digitalWrite(25, LOW);
    delay(1000);
  }
}
