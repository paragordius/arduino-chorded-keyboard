#!/bin/bash

echo "Press enter after putting your Arduino into DFU-mode..."
read
sudo dfu-programmer atmega16u2 erase
sudo dfu-programmer atmega16u2 flash --debug 1 ~/Downloads/Arduino-keyboard-0.3.hex
sudo dfu-programmer atmega16u2 reset
echo "Press enter after you plug-cycle!"
read
#sudo chmod 666 /dev/ttyACM0
echo "Done!"
