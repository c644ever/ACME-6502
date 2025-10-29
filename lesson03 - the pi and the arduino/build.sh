#!/bin/bash
# build.sh - Learning About Build Automation

# The first line tells the computer this is a bash script
# It's like saying "Hey computer, run this as a script!"

# ECHO = Display messages to the user
echo "🔧 Arduino Build Script Starting..."

# This command COMPILES your code:
# - "arduino-cli" = the Arduino command line tool
# - "compile" = convert code to machine language  
# - "--fqbn arduino:avr:mega" = For Arduino Mega board
# - "." = use all files in current folder
echo "Step 1: Compiling (checking code for errors)..."
arduino-cli compile --fqbn arduino:avr:mega .

# This command UPLOADS to Arduino:
# - "upload" = send program to board
# - "-p /dev/ttyUSB0" = port where Arduino is connected
# - "--fqbn arduino:avr:mega" = board type (same as above)
# - "." = files to upload
echo "Step 2: Uploading (sending to Arduino)..."
arduino-cli upload -p /dev/ttyUSB0 --fqbn arduino:avr:mega .

# Success message
echo "✅ Build complete! LEDs should be lighting up."
echo ""
echo "💡 Tip: Without this script, you'd have to type both"
echo "      long commands every time. Now just type ./build.sh!"