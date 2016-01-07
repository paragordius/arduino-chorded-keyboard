#!/bin/bash

echo "Press enter after putting your Arduino into DFU-mode..."
read
sudo dfu-programmer atmega16u2 erase
sudo dfu-programmer atmega16u2 flash --debug 1 ~/Downloads/Arduino-usbserial-uno.hex
sudo dfu-programmer atmega16u2 reset
echo "Press enter after you plug-cycle (twice for good luck)!"
read
sudo chmod 666 /dev/ttyACM*
echo "Done!"
