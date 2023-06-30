# LoRa based mesh network

## Abstract

Our project consisted of equipping a forest with a mesh network built using LoRa wireless technology. In this process, the individual nodes are supposed to receive the messages and forward them to the gateway and vice versa. In addition, an automatic route is to be found that transmits the messages depending on the respective signal strength of the nodes located nearby. If a node has shut down, the route changes so that reliable data transfer continues.

## Used devices

- Heltec WiFi Lora 32 V2
- various LoRa compatible antennas

## Used libraries

- [HelTecAutomation/Heltec_ESP32](https://github.com/HelTecAutomation/Heltec_ESP32/tree/master)
- [hallard/RadioHead](https://github.com/hallard/RadioHead)
- [yoprogramo/QRcodeDisplay](https://github.com/yoprogramo/QRcodeDisplay)

## Interface Specification

To be compatible with the massage format that the gateway understand, we created the following interface specification.

[Interface Specification](doc/interface.md)

## How it works

The directory `src/` contains the source code for the project. Before the program can be started, all necessary settings must be made in `config.h`.
The main program is executed in `main.cpp`.

Tested with PlatformIO and Visual Studio Code.

## Known issues

- Automatic route detection does not work (most likely because of a bug in the RadioHead library)
