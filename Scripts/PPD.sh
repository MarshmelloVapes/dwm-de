#!/bin/bash

clear

current_profile=$(powerprofilesctl get)

echo "=============================="
echo "        Power Profile         "
echo "=============================="
echo "Current: $current_profile"
echo "=============================="
echo "a) Performance"
echo "b) Balanced"
echo "c) Power Saver"
echo "q) Quit"
echo "=============================="

read -rp "Select an option: " choice

case "$choice" in
  a|A)
    echo "Setting power profile to Performance."
    powerprofilesctl set performance
    sleep 1
    ;;
  b|B)
    echo "Setting power profile to Balanced."
    powerprofilesctl set balanced
    sleep 1
    ;;
  c|C)
    echo "Setting power profile to Power Saver."
    powerprofilesctl set power-saver
    sleep 1
    ;;
  q|Q)
    echo "Quitting program."
    exit 0
    ;;
  *)
    echo "Invalid selection"
    ;;
esac
