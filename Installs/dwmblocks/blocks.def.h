//Modify this file to change what commands output to your statusbar, and recompile using the make command.

// static const Block blocks[] = {
//     {"^c#fabd2f^RAM ", "free -m | awk '/Mem:/ {printf \"%d%%\", $3*100/$2 }'", 5, 0},
//     // {"^c#83a598^VOL ", "pactl get-sink-volume @DEFAULT_SINK@ | awk -F'/' '{print $2}' | tr -d ' '", 2, 0},
//     {"^c#83a598^VOL ", "~/.scripts/volume.sh", 2, 0},
//     {"^c#fb4934^BAT ", "cat /sys/class/power_supply/BAT0/capacity | awk '{printf \"%s%%\", $1}'", 30, 0},
//     {"^c#d3869b^",     "date '+%d %b %H:%M'", 60, 0},
// };
static const Block blocks[] = {
    {"^c#fabd2f^RAM ", "free -m | awk '/Mem:/ {printf \"%d%%\", $3*100/$2 }'", 5, 0},
    {"^c#ebdbb2^ | ^d^", NULL, 0, 0},

    {"^c#83a598^VOL ", "~/.scripts/volume.sh", 0, 10},
    {"^c#ebdbb2^ | ^d^", NULL, 0, 0},

    {"^c#fb4934^BAT ", "cat /sys/class/power_supply/BAT0/capacity | awk '{printf \"%s%%\", $1}'", 30, 0},
    {"^c#ebdbb2^ | ^d^", NULL, 0, 0},

    {"^c#d3869b^", "date '+%d %b %H:%M'", 60, 0},
};

//sets delimiter between status commands. NULL character ('\0') means no delimiter.
static char delim[] = "\0";
static unsigned int delimLen = 5;
