#!/bin/bash

AC_PATH="/sys/class/power_supply/AC/online"

last_state=""

while true; do
    current_state="$(cat "$AC_PATH" 2>/dev/null)"

    if [ "$current_state" != "$last_state" ]; then
        ~/.scripts/display-power.sh
        last_state="$current_state"
    fi

    sleep 5
done
