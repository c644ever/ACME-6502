#!/bin/bash
echo "Compiling blink_serial"
if ! arduino-cli compile --fqbn arduino:avr:mega blink_serial/; then
    echo "Compilation failed!"
    exit 1
fi

echo "Upload Sketch to  Arduino"
if ! arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:mega blink_serial/; then
    echo "Upload failed!"
    exit 1
fi
echo "Success..."
echo "Watch Arduino LEDs"
echo "Press anykey to see the serial output of arduino"
echo "LED on und LED off"
echo "quit minicom with ctrl+a q "
read -n 1 -s
minicom -b 115200 -o -D /dev/ttyACM0

