#!/bin/bash

AC_PATH="/sys/class/power_supply/AC/online"

if [ "$(cat "$AC_PATH" 2>/dev/null)" = "1" ]; then
    # AC power: keep display on
    xset s off
    xset -dpms
else
    # Battery: display off after 5 minutes
    xset s on
    xset s 300 300
    xset +dpms
    xset dpms 0 0 300
fi
