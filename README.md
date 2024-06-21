
# HPA FCU

This project represents a custom FCU for HPA engines with one valve.

## Material

- 1x [ESP8266 / D1 Mini](https://www.az-delivery.de/collections/esp8266/products/d1-mini)
- 2x Buttons
- some cable

## Required devices

- Soldering iron

## Assembly

| ![top view](./images/top.jpeg) | ![bottom view](./images/bottom.jpeg) |
| ---------------------------- | ---------------------------------- |
| top view                     | bottom view                        |

1. solder the d1 mini  to some pins
2. connect the D3 pin with both buttons
3. connect the trigger button with the GND-Pin
4. connect the fire selector button with the D8-Pin
5. open the firmware in arduino studio
6. set baudrate to 115000
7. connect the d1 with your computer
8. upload firmware to the d1 mini
