#!/bin/bash
echo "Compiliere den Sketch blink_serial"
if ! arduino-cli compile --fqbn arduino:avr:mega blink_serial/; then
    echo "Compilation failed!"
    exit 1
fi

echo "Lade den Sketch auf den Arduino"
if ! arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:mega blink_serial/; then
    echo "Upload failed!"
    exit 1
fi
echo"Success..."
echo "Beobachte die LEDs auf dem Arduino"
echo "Wenn du eine Taste drückst, sollte minicom starten und du kannst die Ausgabe des Arduinos sehen"
echo "LED ein und LED aus"
echo "mit ctrl+a q kannst du minicom beenden"
read -n 1 -s
minicom -b 115200 -o -D /dev/ttyACM0

