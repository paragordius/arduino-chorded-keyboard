#!/bin/bash

firmware_loaction=~/Downloads/Arduino-keyboard-0.3.hex

echo "Press enter after putting your Arduino into DFU-mode..."
read
sudo dfu-programmer atmega16u2 erase
sudo dfu-programmer atmega16u2 flash --debug 1 $firmware_location
sudo dfu-programmer atmega16u2 reset
echo "Press enter after you plug-cycle!"
read

echo "Done!"
