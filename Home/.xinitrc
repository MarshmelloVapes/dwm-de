udiskctl mount -b /dev/mmcblk0p1 &
~/.scripts/ppd-watcher &
~/.scripts/display-power-monitor.sh &

# Export the X11 environment for desktop portals
systemctl --user import-environment DISPLAY XAUTHORITY
dbus-update-activation-environment --systemd DISPLAY XAUTHORITY

exec dwm
