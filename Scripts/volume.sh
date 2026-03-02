#!/usr/bin/env bash

# Get default sink
SINK=$(pactl get-default-sink)

# Get volume (first channel, as percentage)
vol=$(pactl get-sink-volume "$SINK" | awk '{print $5}' | head -n1)

# Get mute status
mute=$(pactl get-sink-mute "$SINK" | awk '{print $2}')

if [ "$mute" = "yes" ]; then
    echo "Muted"
else
    echo "${vol}"
fi
