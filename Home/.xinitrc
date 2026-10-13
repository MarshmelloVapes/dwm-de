udiskctl mount -b /dev/mmcblk0p1 &
~/.scripts/ppd-watcher &
~/.scripts/display-power-monitor.sh &

exec dwm
