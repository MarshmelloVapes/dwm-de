#!/usr/bin/env bash

# Get current brightness value
current=$(brightnessctl g)

# Get max brightness value
max=$(brightnessctl m)

# Calculate percentage
brightness=$(( current * 100 / max ))

# Output brightness percentage
echo "${brightness}%"
